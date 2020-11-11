#include "TktkDX12Game/DXGameResource/GameObjectResouse/Component/DefaultComponents/StateMachine/StateMachineList.h"

#ifdef _DEBUG
#include <stdexcept>
#endif // _DEBUG

#include "TktkDX12Game/DXGameResource/GameObjectResouse/GameObject/GameObject.h"
#include "TktkDX12Game/DXGameResource/GameObjectResouse/Component/DefaultComponents/StateMachine/StateMachine.h"
#include "TktkDX12Game/DXGameResource/GameObjectResouse/Component/DefaultComponents/StateMachine/Structs/StateTypeList.h"
#include "TktkDX12Game/DXGameResource/GameObjectResouse/Component/DefaultComponents/StateMachine/Structs/StateTypeHierarchy.h"

namespace tktk
{
	StateMachineList::StateMachineList(const StateMachineListInitParam& initParam, const GameObjectPtr& user)
	{
		// 親の状態を持たないステートマシンを作る
		for (const auto& node : initParam.m_roots)
		{
			// ステートマシンを作って
			auto createdComponent = user->createComponent<StateMachine>(node.m_id);

			// ステートマシンリストに登録する
			m_stateMachineList[node.m_id] = { createdComponent, {} };

			// 親の状態を持つステートマシンを作るために再起処理を行う
			createNode(m_stateMachineList.at(node.m_id), node, user);
		}
	}

	void StateMachineList::setTargetHierarchy(const StateTypeHierarchy& targetHierarchy)
	{
		m_targetHierarchy = targetHierarchy;
	}

	bool StateMachineList::isSetTargetHierarchy() const
	{
		return !getTargetStateMachine().expired();
	}

	void StateMachineList::addChild(const GameObjectPtr& child)
	{
		auto targetStateMachine = getTargetStateMachine();

		if (targetStateMachine.expired()) return;

		targetStateMachine->addChild(child);
	}

	void StateMachineList::removeChild(const GameObjectPtr& child)
	{
		// 全ての階層から引数のオブジェクトを削除するために再帰する
		removeChildImpl(m_stateMachineList, child);
	}

	void StateMachineList::addComponent(const ComponentBasePtr& componentPtr)
	{
		auto targetStateMachine = getTargetStateMachine();

		if (targetStateMachine.expired()) return;

		targetStateMachine->addComponent(componentPtr);
	}

	void StateMachineList::createNode(StateMachineList::Node& parentNode, const StateMachineListInitParam::Node& nodeInitParam, const GameObjectPtr& user)
	{
		// 親の状態を持つステートマシンを作る
		for (const auto& node : nodeInitParam.m_children)
		{
			// ステートマシンを作って
			auto createdComponent = user->createComponent<StateMachine>(node.m_id);

			// 親のステートマシンに登録し
			parentNode.m_stateMachine->addComponent(ComponentBasePtr(createdComponent));

			// ステートマシンリストに登録する
			parentNode.m_childNode[node.m_id] = { createdComponent, {} };

			// さらなる子要素を作るために再起する
			createNode(parentNode.m_childNode.at(node.m_id), node, user);
		}
	}

	ComponentPtr<StateMachine> StateMachineList::getTargetStateMachine() const
	{
		// 現在の階層を表すポインタ
		const StateMachineList::Node* curNodePtr = nullptr;

		// 対象のステートの階層をループする
		for (const auto& node : m_targetHierarchy.hierarchy)
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

		// 「現在の階層を表すポインタ」が nullptr でなければ対象のステートマシンを、nullptr だったら空のコンポーネントポインタを返す
		return (curNodePtr != nullptr) ? curNodePtr->m_stateMachine : ComponentPtr<StateMachine>();
	}

	void StateMachineList::removeChildImpl(const std::unordered_map<StateTypeCarrier, Node>& targetMap, const GameObjectPtr& child)
	{
		for (const auto& pair : targetMap)
		{
			pair.second.m_stateMachine->removeChild(child);

			// 再帰処理
			removeChildImpl(pair.second.m_childNode, child);
		}
	}
}