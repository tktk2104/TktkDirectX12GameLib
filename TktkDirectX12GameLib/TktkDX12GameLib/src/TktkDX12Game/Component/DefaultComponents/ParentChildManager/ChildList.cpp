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
		// �O�t���[���Œǉ����ꂽ�Q�[���I�u�W�F�N�g�����C�����X�g�Ɉړ�����
		m_childList.splice_after(m_childList.before_begin(), std::move(m_newComponentList));

		// ����ł���Q�[���I�u�W�F�N�g�����C�����X�g����폜����
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