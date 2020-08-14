#include "TktkDX12Game/Component/ComponentGameObjectFunc/GameObjectComponentList.h"

namespace tktk
{
	void GameObjectComponentList::runHandleMessageAll(unsigned int messageId, const MessageAttachment& value) const
	{
		for (const auto& node : m_componentList)
		{
			node.runHandleMessage(value, messageId);
		}
	}

	void GameObjectComponentList::runAfterChangeParentAll(const GameObjectPtr& beforParent) const
	{
		for (const auto& node : m_componentList)
		{
			node.runAfterChangeParent(beforParent);
		}
	}

	void GameObjectComponentList::runOnCollisionEnterAll(const GameObjectPtr& other) const
	{
		for (const auto& node : m_componentList)
		{
			node.runOnCollisionEnter(other);
		}
	}

	void GameObjectComponentList::runOnCollisionStayAll(const GameObjectPtr& other) const
	{
		for (const auto& node : m_componentList)
		{
			node.runOnCollisionStay(other);
		}
	}

	void GameObjectComponentList::runOnCollisionExitAll(const GameObjectPtr& other) const
	{
		for (const auto& node : m_componentList)
		{
			node.runOnCollisionExit(other);
		}
	}

	void GameObjectComponentList::destroyAll() const
	{
		for (const auto& node : m_componentList)
		{
			node.destroy();
		}
	}

	void GameObjectComponentList::movePreFrameAddedNode()
	{
		// メインリストに移動する情報が入ったリストの要素をメインリストに移動
		m_componentList.splice_after(std::begin(m_componentList), std::move(m_nextFrameAddNodeList));

		// コピー元のコンテナは削除
		m_nextFrameAddNodeList.clear();
	}

	void GameObjectComponentList::removeDeadComponent()
	{
		// 死亡フラグの立ったコンポーネントをリストから削除する
		m_componentList.remove_if([](const auto& node) { return node.isDead(); });
	}
}