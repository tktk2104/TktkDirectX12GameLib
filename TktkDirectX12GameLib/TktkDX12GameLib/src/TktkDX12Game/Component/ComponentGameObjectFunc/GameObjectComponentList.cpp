#include "TktkDX12Game/Component/ComponentGameObjectFunc/GameObjectComponentList.h"

namespace tktk
{
	void GameObjectComponentList::runHandleMessageAll(unsigned int messageId, const MessageAttachment& value) const
	{
		for (const auto& component : m_componentList)
		{
			component.runHandleMessage(value, messageId);
		}
	}

	void GameObjectComponentList::runAfterChangeParentAll(const GameObjectPtr& beforParent) const
	{
		for (const auto& component : m_componentList)
		{
			component.runAfterChangeParent(beforParent);
		}
	}

	void GameObjectComponentList::runOnCollisionEnterAll(const GameObjectPtr& other)
	{
		// 現在のフレームで既に衝突処理が呼ばれた組み合わせの場合、何もしない
		for (const auto& curFrameHitObject : m_curFrameHitObjectList)
		{
			if (curFrameHitObject.isSame(other)) return;
		}

		// 現在のフレームで衝突処理を行ったオブジェクトリストに衝突相手のオブジェクトポインタを追加する
		m_curFrameHitObjectList.push_front(other);

		for (const auto& component : m_componentList)
		{
			component.runOnCollisionEnter(other);
		}
	}

	void GameObjectComponentList::runOnCollisionStayAll(const GameObjectPtr& other)
	{
		// 現在のフレームで既に衝突処理が呼ばれた組み合わせの場合、何もしない
		for (const auto& curFrameHitObject : m_curFrameHitObjectList)
		{
			if (curFrameHitObject.isSame(other)) return;
		}

		// 現在のフレームで衝突処理を行ったオブジェクトリストに衝突相手のオブジェクトポインタを追加する
		m_curFrameHitObjectList.push_front(other);

		for (const auto& component : m_componentList)
		{
			component.runOnCollisionStay(other);
		}
	}

	void GameObjectComponentList::runOnCollisionExitAll(const GameObjectPtr& other)
	{
		// 現在のフレームで既に衝突処理が呼ばれた組み合わせの場合、何もしない
		for (const auto& curFrameHitObject : m_curFrameHitObjectList)
		{
			if (curFrameHitObject.isSame(other)) return;
		}

		// 現在のフレームで衝突処理を行ったオブジェクトリストに衝突相手のオブジェクトポインタを追加する
		m_curFrameHitObjectList.push_front(other);

		for (const auto& component : m_componentList)
		{
			component.runOnCollisionExit(other);
		}
	}

	void GameObjectComponentList::clearHitObjectList()
	{
		m_curFrameHitObjectList.clear();
	}

	void GameObjectComponentList::destroyAll() const
	{
		for (const auto& component : m_nextFrameAddNodeList)
		{
			component.destroy();
		}

		for (const auto& component : m_componentList)
		{
			component.destroy();
		}
	}

	void GameObjectComponentList::movePreFrameAddedNode()
	{
		// メインリストに移動する情報が入ったリストの要素をメインリストに移動
		for (const auto& node : m_nextFrameAddNodeList)
		{
			m_componentList.push_front(node);
		}

		// コピー元のコンテナは削除
		m_nextFrameAddNodeList.clear();
	}

	void GameObjectComponentList::removeDeadComponent()
	{
		// 死亡フラグの立ったコンポーネントをリストから削除する
		m_componentList.remove_if([](const auto& node) { return node.isDead(); });
	}
}