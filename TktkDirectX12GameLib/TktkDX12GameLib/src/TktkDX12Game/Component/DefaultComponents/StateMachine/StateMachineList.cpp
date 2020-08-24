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
			auto createdComponent = DX12GameManager::createComponent<StateMachine>(node.m_id);

			// 引数のGameObjectを設定し
			createdComponent.lock()->setUser(user);

			// ステートマシンリストに登録する
			m_stateMachineList[node.m_id] = { componentList->add<StateMachine>(createdComponent), {} };

			// 親の状態を持つステートマシンを作るために再起処理を行う
			createNode(m_stateMachineList.at(node.m_id), node, user, componentList);
		}
	}

	void StateMachineList::addChild(const std::vector<int>& targetState, const GameObjectPtr& child)
	{
		getTarget(targetState)->addChild(child);
	}

	void StateMachineList::addComponent(const std::vector<int>& targetState, const ComponentBasePtr& componentPtr)
	{
		getTarget(targetState)->addComponent(componentPtr);
	}

	void StateMachineList::createNode(StateMachineList::Node& parentNode, const StateMachineListInitParam::Node& nodeInitParam, const GameObjectPtr& user, const std::unique_ptr<GameObjectComponentList>& componentList)
	{
		// 親の状態を持つステートマシンを作る
		for (const auto& node : nodeInitParam.m_child)
		{
			// ステートマシンを作って
			auto createdComponent = DX12GameManager::createComponent<StateMachine>(node.m_id);

			// 引数のGameObjectを設定し
			createdComponent.lock()->setUser(user);

			// 親のステートマシンに登録し
			parentNode.m_stateMachine->addComponent(ComponentBasePtr(createdComponent));

			// ステートマシンリストに登録する
			parentNode.m_childNode[node.m_id] = { componentList->add<StateMachine>(createdComponent), {} };

			// さらなる子要素を作るために再起する
			createNode(parentNode.m_childNode.at(node.m_id), node, user, componentList);
		}
	}

	ComponentPtr<StateMachine> StateMachineList::getTarget(const std::vector<int>& targetState) const
	{
#ifdef _DEBUG
		if (targetState.size() == 0)  throw std::runtime_error("targetState fraud value");
#endif // _DEBUG

		const StateMachineList::Node* curNodePtr = nullptr;

		for (int node : targetState)
		{
			// ※初回ループ時のみアルゴリズムが違う
			if (curNodePtr == nullptr)
			{
#ifdef _DEBUG
				if (m_stateMachineList.count(node) == 0)  throw std::runtime_error("targetState fraud value");
#endif // _DEBUG

				curNodePtr = &m_stateMachineList.at(node);
				continue;
			}

#ifdef _DEBUG
			if (m_stateMachineList.count(node) == 0)  throw std::runtime_error("targetState fraud value");
#endif // _DEBUG

			curNodePtr = &curNodePtr->m_childNode.at(node);
		}

		if (curNodePtr != nullptr) return curNodePtr->m_stateMachine;

#ifdef _DEBUG
		else  throw std::runtime_error("targetState fraud value");
#endif // _DEBUG
		return ComponentPtr<StateMachine>();
	}
}