#include "TktkDX12Game/DXGameResource/GameObjectResouse/Component/ComponentMainList/ComponentMainList.h"

#include "TktkDX12Game/DXGameResource/GameObjectResouse/Component/ComponentMainList/ComponentTypeList.h"

namespace tktk
{
	// コンストラクタを非インライン化する
	ComponentMainList::ComponentMainList() = default;

	// デストラクタを非インライン化する
	ComponentMainList::~ComponentMainList() = default;

	void ComponentMainList::addComponent(std::type_index type, ComponentListVTable* vtablePtr, const std::shared_ptr<ComponentBase>& componentPtr)
	{
		// テンプレート引数のコンポーネントが以前に追加された事があるか調べる
		auto findNode = m_addComponentMap.find(type);

		// もし、今回が初めて追加される種類のコンポーネントだった場合、
		if (findNode == std::end(m_addComponentMap))
		{
			auto createList = std::make_shared<ComponentTypeList>(vtablePtr);
			m_mainMap.emplace(m_priorityList.getPriority(type), createList);
			m_addComponentMap.emplace(type, createList);

			// 追加したリストを取得する
			findNode = m_addComponentMap.find(type);
		}

		findNode->second.lock()->addComponent(componentPtr);
	}

	void ComponentMainList::addRunFuncPriority(std::type_index type, float priority)
	{
		m_priorityList.addPriority(type, priority);
	}

	void ComponentMainList::movePreFrameAddedNode()
	{
		// 前フレームに追加した要素を本リストに追加する
		for (const auto& node : m_mainMap)
		{
			node.second->moveNewComponent();
		}
	}

	void ComponentMainList::activeChangeCheck()
	{
		// アクティブフラグの判定とフラグ変更時の関数呼び出し処理
		for (const auto& node : m_mainMap)
		{
			node.second->activeChangeCheck();
		}
	}

	void ComponentMainList::update()
	{
		// 「update」関数呼び出し処理
		for (const auto& node : m_mainMap)
		{
			node.second->runUpdate();
		}
	}

	void ComponentMainList::runBeforeCollide()
	{
		// 「runAfterCollide」関数呼び出し処理
		for (const auto& node : m_mainMap)
		{
			node.second->runBeforeCollide();
		}
	}

	void ComponentMainList::runAfterCollide()
	{
		// 「runAfterCollide」関数呼び出し処理
		for (const auto& node : m_mainMap)
		{
			node.second->runAfterCollide();
		}
	}

	void ComponentMainList::removeDeadComponent()
	{
		// 「runAfterCollide」関数呼び出し処理
		for (const auto& node : m_mainMap)
		{
			node.second->removeDeadComponent();
		}
	}
}