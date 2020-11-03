#include "TktkDX12Game/Component/DefaultComponents/StateMachine/StateMachineList.h"

#ifdef _DEBUG
#include <stdexcept>
#endif // _DEBUG

#include "TktkDX12Game/_MainManager/DX12GameManager.h"
#include "TktkDX12Game/Component/ComponentGameObjectFunc/GameObjectComponentList.h"
#include "TktkDX12Game/Component/DefaultComponents/StateMachine/StateMachine.h"

namespace tktk
{
	StateMachineList::StateMachineList(const StateMachineListInitParam& initParam, const GameObjectPtr& user, const std::unique_ptr<GameObjectComponentList>& componentList)
	{
		// 親の状態を持たないステートマシンを作る
		for (const auto& node : initParam.m_roots)
		{
			// ステートマシンを作って
			auto createdComponent = DX12GameManager::createComponent<StateMachine>(user, node.m_id);

			// ステートマシンリストに登録する
			m_stateMachineList[node.m_id] = { componentList->add<StateMachine>(createdComponent), {} };

			// 親の状態を持つステートマシンを作るために再起処理を行う
			createNode(m_stateMachineList.at(node.m_id), node, user, componentList);
		}
	}

	void StateMachineList::addChild(const StateTypeHierarchy& targetState, const GameObjectPtr& child)
	{
		(*getTarget(targetState)).m_stateMachine->addChild(child);
	}

	void StateMachineList::addComponent(const StateTypeHierarchy& targetState, const ComponentBasePtr& componentPtr)
	{
		(*getTarget(targetState)).m_stateMachine->addComponent(componentPtr);
	}

	StateTypeList StateMachineList::getChildNode(const StateTypeHierarchy& targetState) const
	{
		// 結果を返すためのコンテナ（重複しないようにsetを使う）
		auto result = StateTypeList();

		// 引数のステートを取得し、再帰関数を呼ぶ
		getChildNodeImpl(&result, getTarget(targetState));

		return result;
	}

	void StateMachineList::createNode(StateMachineList::Node& parentNode, const StateMachineListInitParam::Node& nodeInitParam, const GameObjectPtr& user, const std::unique_ptr<GameObjectComponentList>& componentList)
	{
		// 親の状態を持つステートマシンを作る
		for (const auto& node : nodeInitParam.m_children)
		{
			// ステートマシンを作って
			auto createdComponent = DX12GameManager::createComponent<StateMachine>(user, node.m_id);

			// 親のステートマシンに登録し
			parentNode.m_stateMachine->addComponent(ComponentBasePtr(createdComponent));

			// ステートマシンリストに登録する
			parentNode.m_childNode[node.m_id] = { componentList->add<StateMachine>(createdComponent), {} };

			// さらなる子要素を作るために再起する
			createNode(parentNode.m_childNode.at(node.m_id), node, user, componentList);
		}
	}

	const StateMachineList::Node* StateMachineList::getTarget(const StateTypeHierarchy& targetState) const
	{
#ifdef _DEBUG
		if (targetState.hierarchy.size() == 0)  throw std::runtime_error("targetState fraud value");
#endif // _DEBUG

		// 現在の階層を表すポインタ
		const StateMachineList::Node* curNodePtr = nullptr;

		// 対象のステートの階層をループする
		for (const auto& node : targetState.hierarchy)
		{
			// ※初回ループ時のみアルゴリズムが違う
			if (curNodePtr == nullptr)
			{
#ifdef _DEBUG
				if (m_stateMachineList.count(node) == 0)  throw std::runtime_error("targetState fraud value");
#endif // _DEBUG

				// 一番上の階層を取得する
				curNodePtr = &m_stateMachineList.at(node);

				// 次の要素へ移行する
				continue;
			}

#ifdef _DEBUG
			if (curNodePtr->m_childNode.count(node) == 0)  throw std::runtime_error("targetState fraud value");
#endif // _DEBUG

			// 次の要素の階層を取得する
			curNodePtr = &curNodePtr->m_childNode.at(node);
		}

		// 現在の階層が不正ではなければその値を返す
		if (curNodePtr != nullptr) return curNodePtr;

#ifdef _DEBUG
		else  throw std::runtime_error("targetState fraud value");
#endif // _DEBUG
		return nullptr;
	}

	void StateMachineList::getChildNodeImpl(StateTypeList* result, const StateMachineList::Node* target) const
	{
		// 子ステートを巡回する
		for (const auto& node : target->m_childNode)
		{
			result->list.insert(node.first);

			// さらなる孫ステートを巡回するための再帰処理
			getChildNodeImpl(result, &node.second);
		}
	}
}