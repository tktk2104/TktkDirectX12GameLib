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

	GameObjectPtr ChildList::findGameObjectWithTag(int tag) const
	{
		for (const auto& node : m_childList)
		{
			if (node->containGameobjectTag(tag)) return node;

			// ���v�f�ōċN����
			auto findGrandchildResult = node->findChildWithTag(tag);

			// ���v�f�őΏۂƂȂ�Q�[���I�u�W�F�N�g���������炻���Ԃ�
			if (!findGrandchildResult.expired()) return findGrandchildResult;
		}
		return GameObjectPtr();
	}

	std::forward_list<GameObjectPtr> ChildList::findGameObjectsWithTag(int tag) const
	{
		std::forward_list<GameObjectPtr> result;

		for (const auto& node : m_childList)
		{
			if (node->containGameobjectTag(tag))
			{
				result.push_front(node);
			}

			// ���v�f�ōċN�������ʂ��������ʃ��X�g�ɒǉ�����
			result.splice_after(result.before_begin(), std::move(node->findChildrenWithTag(tag)));
		}
		return result;
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