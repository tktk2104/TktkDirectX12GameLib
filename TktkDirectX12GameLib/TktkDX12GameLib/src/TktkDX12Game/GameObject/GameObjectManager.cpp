#include "TktkDX12Game/GameObject/GameObjectManager.h"

#include "TktkDX12Game/GameObject/GameObject.h"

namespace tktk
{
	void GameObjectManager::update()
	{
		// 死亡フラグの立ったオブジェクトを削除する
		m_gameObjectList.remove_if([](const auto& node) { return node->isDead(); });

		for (const auto& node : m_gameObjectList)
		{
			node->update();
		}
	}

	void GameObjectManager::runHandleMessageAll(unsigned int messageId, const MessageAttachment& value)
	{
		for (const auto& node : m_gameObjectList)
		{
			node->runHandleMessageAll(messageId, value);
		}
	}

	GameObjectPtr GameObjectManager::createGameObject()
	{
		auto gameObject = std::make_shared<GameObject>();

		m_gameObjectList.push_front(gameObject);

		return GameObjectPtr(gameObject);
	}

	GameObjectPtr GameObjectManager::findGameObjectWithTag(int tag) const
	{
		for (const auto& node : m_gameObjectList)
		{
			if (node->containGameobjectTag(tag)) return GameObjectPtr(node);
		}
		return GameObjectPtr();
	}

	std::forward_list<GameObjectPtr> GameObjectManager::findGameObjectsWithTag(int tag) const
	{
		std::forward_list<GameObjectPtr> result;

		for (const auto& node : m_gameObjectList)
		{
			if (node->containGameobjectTag(tag))
			{
				result.push_front(GameObjectPtr(node));
			}
		}
		return result;
	}
}