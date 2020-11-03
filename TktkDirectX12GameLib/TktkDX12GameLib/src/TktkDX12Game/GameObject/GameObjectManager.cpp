#include "TktkDX12Game/GameObject/GameObjectManager.h"

#include "TktkDX12Game/GameObject/GameObject.h"

namespace tktk
{
	void GameObjectManager::update()
	{
		for (const auto& node : m_gameObjectList)
		{
			node->update();
		}
	}

	void GameObjectManager::movePreFrameAddedNode()
	{
		m_gameObjectList.splice_after(m_gameObjectList.before_begin(), std::move(m_newGameObjectList));
	}

	void GameObjectManager::removeDeadObject()
	{
		// 死亡フラグの立ったオブジェクトを削除する
		m_gameObjectList.remove_if([](const auto& node) { return node->isDead(); });
	}

	void GameObjectManager::runHandleMessageAll(MessageTypeCarrier type, const MessageAttachment& attachment)
	{
		for (const auto& node : m_gameObjectList)
		{
			node->runHandleMessageAll(type, attachment);
		}
	}

	GameObjectPtr GameObjectManager::createGameObject()
	{
		auto gameObject = std::make_shared<GameObject>();

		m_newGameObjectList.push_front(gameObject);

		return GameObjectPtr(gameObject);
	}

	GameObjectPtr GameObjectManager::findGameObjectWithTag(GameObjectTagCarrier tag) const
	{
		for (const auto& node : m_gameObjectList)
		{
			if (node->containGameobjectTag(tag)) return GameObjectPtr(node);
		}
		return GameObjectPtr();
	}

	std::forward_list<GameObjectPtr> GameObjectManager::findGameObjectsWithTag(GameObjectTagCarrier tag) const
	{
		std::forward_list<GameObjectPtr> result;

		for (const auto& node : m_gameObjectList)
		{
			if (node->containGameobjectTag(tag)) result.push_front(GameObjectPtr(node));
		}
		return result;
	}

	void GameObjectManager::destroyGameObjectsWithTag(GameObjectTagCarrier tag)
	{
		for (const auto& node : m_newGameObjectList)
		{
			if (node->containGameobjectTag(tag)) node->destroy();
		}

		for (const auto& node : m_gameObjectList)
		{
			if (node->containGameobjectTag(tag)) node->destroy();
		}
	}
}