#include "TktkDX12Game/Component/DefaultComponents/ParentChildManager/ChildList.h"

#include <algorithm>
#include "TktkDX12Game/GameObject/GameObject.h"

namespace tktk
{
	void ChildList::addChild(const GameObjectPtr& child)
	{
		m_newComponentList.push_front(child);
	}

	const std::forward_list<GameObjectPtr>& ChildList::getChildren() const
	{
		return m_childList;
	}

	void ChildList::updateContainer()
	{
		// 前フレームで追加されたゲームオブジェクトをメインリストに移動する
		m_childList.splice_after(m_childList.before_begin(), std::move(m_newComponentList));

		// 死んでいるゲームオブジェクトをメインリストから削除する
		m_childList.remove_if([](const GameObjectPtr& node) { return node.expired(); });
	}

	void ChildList::remove(const GameObjectPtr& gameObject)
	{
		m_childList.remove_if([gameObject](const GameObjectPtr& node) { return (node.isSame(gameObject)); });
	}

	void ChildList::destroyAll()
	{
		for (const auto& node : m_childList)
		{
			node->destroy();
		}
	}

	void ChildList::sendMessage(unsigned int messageId, const MessageAttachment& value)
	{
		for (const auto& node : m_childList)
		{
			node->sendMessage(messageId, value);
		}
	}
}