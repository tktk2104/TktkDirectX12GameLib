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
		// ���C�����X�g�Ɉړ������񂪓��������X�g�̗v�f�����C�����X�g�Ɉړ�
		m_componentList.splice_after(std::begin(m_componentList), std::move(m_nextFrameAddNodeList));

		// �R�s�[���̃R���e�i�͍폜
		m_nextFrameAddNodeList.clear();
	}

	void GameObjectComponentList::removeDeadComponent()
	{
		// ���S�t���O�̗������R���|�[�l���g�����X�g����폜����
		m_componentList.remove_if([](const auto& node) { return node.isDead(); });
	}
}