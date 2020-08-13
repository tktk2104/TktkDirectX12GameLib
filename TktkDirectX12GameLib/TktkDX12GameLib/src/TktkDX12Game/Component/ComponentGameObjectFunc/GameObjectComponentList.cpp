#include "TktkDX12Game/Component/ComponentGameObjectFunc/GameObjectComponentList.h"

namespace tktk
{
	void GameObjectComponentList::runHandleMessageAll(unsigned int messageId, const MessageAttachment& value)
	{
		for (auto& node : m_componentList)
		{
			node.runHandleMessage(value, messageId);
		}
	}

	void GameObjectComponentList::runAfterChangeParentAll(const GameObjectPtr& beforParent)
	{
		for (auto& node : m_componentList)
		{
			node.runAfterChangeParent(beforParent);
		}
	}

	void GameObjectComponentList::runOnCollisionEnterAll(const GameObjectPtr& other)
	{
		for (auto& node : m_componentList)
		{
			node.runOnCollisionEnter(other);
		}
	}

	void GameObjectComponentList::runOnCollisionStayAll(const GameObjectPtr& other)
	{
		for (auto& node : m_componentList)
		{
			node.runOnCollisionStay(other);
		}
	}

	void GameObjectComponentList::runOnCollisionExitAll(const GameObjectPtr& other)
	{
		for (auto& node : m_componentList)
		{
			node.runOnCollisionExit(other);
		}
	}

	void GameObjectComponentList::destroyAll()
	{
		for (auto& node : m_componentList)
		{
			node.destroy();
		}
	}

	void GameObjectComponentList::removeDeadComponent()
	{
		m_componentList.remove_if([this](const auto& node) { return node.isDead(); });
	}
}