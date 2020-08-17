#include "TktkDX12Game/Component/ComponentManager.h"

#include "TktkDX12Game/Component/ComponentMainList.h"

namespace tktk
{
	void ComponentManager::update()
	{
		// 前フレームに追加されたコンポーネントをメインリストに追加する
		for (const auto& node : m_mainMap)
		{
			node.second->moveNewComponent();
		}
		m_startList.movePreFrameAddedNode();
		m_collisionList.movePreFrameAddedNode();
		m_drawList.movePreFrameAddedNode();

		// アクティブフラグの判定とフラグ変更時の関数呼び出し処理
		for (const auto& node : m_mainMap)
		{
			node.second->activeChangeCheck();
		}

		// 「start()」関数呼び出し処理
		m_startList.runStartFunc();
		
		// 「update()」関数呼び出し処理
		for (const auto& node : m_mainMap)
		{
			node.second->runUpdate();
		}

		// 衝突判定系関数呼び出し処理
		m_collisionList.runCollisionFunc();

		// 「afterCollide()」関数呼び出し処理
		for (const auto& node : m_mainMap)
		{
			node.second->runAfterCollide();
		}
	}

	void ComponentManager::removeDeadComponent()
	{
		// メインリストが管理しているコンポーネントポインタの生存確認
		for (const auto& node : m_mainMap)
		{
			node.second->removeDeadComponent();
		}

		// 衝突判定リストが管理しているコンポーネントポインタの生存確認
		m_collisionList.removeDeadComponent();

		// 描画リストが管理しているコンポーネントポインタの生存確認
		m_drawList.removeDeadComponent();
	}

	void ComponentManager::draw()
	{
		// 「draw()」関数呼び出し処理
		m_drawList.runDrawFunc();
	}

	void ComponentManager::addCollisionGroup(int firstGroup, int secondGroup)
	{
		// 衝突判定の組み合わせを追加
		m_collisionList.addCollisionGroup(firstGroup, secondGroup);
	}
}