#include "TktkDX12Game/Component/DefaultComponents/ParentChildManager/ParentChildManager.h"

namespace tktk
{
	void ParentChildManager::updateContainer()
	{
		m_childList.updateContainer();
	}

	void ParentChildManager::runAfterChangeParentAll(const GameObjectPtr& beforParent)
	{
		const auto& user = getGameObject();
		if (user.expired()) return;
		user->runAfterChangeParentAll(beforParent);
	}

	void ParentChildManager::removeChild(const GameObjectPtr& child)
	{
		m_childList.remove(child);
	}

	void ParentChildManager::destroyChildren()
	{
		m_childList.destroyAll();
	}

	const GameObjectPtr& ParentChildManager::getParent() const
	{
		return m_parent;
	}

	void ParentChildManager::setParent(const GameObjectPtr& parent)
	{
		m_parent = parent;
	}

	const std::forward_list<GameObjectPtr>& ParentChildManager::getChildren() const
	{
		return m_childList.getChildren();
	}

	GameObjectPtr ParentChildManager::findGameObjectWithTag(int tag) const
	{
		return m_childList.findGameObjectWithTag(tag);
	}

	std::forward_list<GameObjectPtr> ParentChildManager::findGameObjectsWithTag(int tag) const
	{
		return m_childList.findGameObjectsWithTag(tag);
	}

	void ParentChildManager::addChild(const GameObjectPtr& child)
	{
		m_childList.addChild(child);
	}

	void ParentChildManager::sendMessage(unsigned int messageId, const MessageAttachment& value)
	{
		m_childList.sendMessage(messageId, value);
	}
}