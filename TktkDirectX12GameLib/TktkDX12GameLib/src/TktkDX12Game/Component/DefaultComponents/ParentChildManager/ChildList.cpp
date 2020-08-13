#include "TktkDX12Game/Component/DefaultComponents/ParentChildManager/ChildList.h"

#include <algorithm>
#include "TktkDX12Game/GameObject/GameObject.h"
#include "..\..\..\..\..\inc\TktkDX12Game\Component\DefaultComponents\ParentChildManager\ChildList.h"

namespace tktk
{
	void ChildList::addChild(const GameObjectPtr& child)
	{
		m_childList.push_front(child);
	}

	const std::forward_list<GameObjectPtr>& ChildList::getChildren() const
	{
		return m_childList;
	}

	void ChildList::updateContainer()
	{
		m_childList.remove_if([](GameObjectPtr& node) { return node.expired(); });
	}

	void ChildList::remove(const GameObjectPtr& gameObject)
	{
		m_childList.remove_if([gameObject](GameObjectPtr& node) { return (node.isSame(gameObject)); });
	}

	void ChildList::destroyAll()
	{
		for (auto& node : m_childList)
		{
			node->destroy();
		}
	}

	void ChildList::sendMessage(unsigned int messageId, const MessageAttachment& value)
	{
		for (auto& node : m_childList)
		{
			node->sendMessage(messageId, value);
		}
	}
}