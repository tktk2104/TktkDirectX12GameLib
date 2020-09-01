#include "TktkDX12Game/Component/ComponentGameObjectFunc/GameObjectComponentList.h"

namespace tktk
{
	void GameObjectComponentList::runHandleMessageAll(unsigned int messageId, const MessageAttachment& value) const
	{
		for (const auto& component : m_componentList)
		{
			component.runHandleMessage(value, messageId);
		}
	}

	void GameObjectComponentList::runAfterChangeParentAll(const GameObjectPtr& beforParent) const
	{
		for (const auto& component : m_componentList)
		{
			component.runAfterChangeParent(beforParent);
		}
	}

	void GameObjectComponentList::runOnCollisionEnterAll(const GameObjectPtr& other)
	{
		// ���݂̃t���[���Ŋ��ɏՓˏ������Ă΂ꂽ�g�ݍ��킹�̏ꍇ�A�������Ȃ�
		for (const auto& curFrameHitObject : m_curFrameHitObjectList)
		{
			if (curFrameHitObject.isSame(other)) return;
		}

		// ���݂̃t���[���ŏՓˏ������s�����I�u�W�F�N�g���X�g�ɏՓˑ���̃I�u�W�F�N�g�|�C���^��ǉ�����
		m_curFrameHitObjectList.push_front(other);

		for (const auto& component : m_componentList)
		{
			component.runOnCollisionEnter(other);
		}
	}

	void GameObjectComponentList::runOnCollisionStayAll(const GameObjectPtr& other)
	{
		// ���݂̃t���[���Ŋ��ɏՓˏ������Ă΂ꂽ�g�ݍ��킹�̏ꍇ�A�������Ȃ�
		for (const auto& curFrameHitObject : m_curFrameHitObjectList)
		{
			if (curFrameHitObject.isSame(other)) return;
		}

		// ���݂̃t���[���ŏՓˏ������s�����I�u�W�F�N�g���X�g�ɏՓˑ���̃I�u�W�F�N�g�|�C���^��ǉ�����
		m_curFrameHitObjectList.push_front(other);

		for (const auto& component : m_componentList)
		{
			component.runOnCollisionStay(other);
		}
	}

	void GameObjectComponentList::runOnCollisionExitAll(const GameObjectPtr& other)
	{
		// ���݂̃t���[���Ŋ��ɏՓˏ������Ă΂ꂽ�g�ݍ��킹�̏ꍇ�A�������Ȃ�
		for (const auto& curFrameHitObject : m_curFrameHitObjectList)
		{
			if (curFrameHitObject.isSame(other)) return;
		}

		// ���݂̃t���[���ŏՓˏ������s�����I�u�W�F�N�g���X�g�ɏՓˑ���̃I�u�W�F�N�g�|�C���^��ǉ�����
		m_curFrameHitObjectList.push_front(other);

		for (const auto& component : m_componentList)
		{
			component.runOnCollisionExit(other);
		}
	}

	void GameObjectComponentList::clearHitObjectList()
	{
		m_curFrameHitObjectList.clear();
	}

	void GameObjectComponentList::destroyAll() const
	{
		for (const auto& component : m_nextFrameAddNodeList)
		{
			component.destroy();
		}

		for (const auto& component : m_componentList)
		{
			component.destroy();
		}
	}

	void GameObjectComponentList::movePreFrameAddedNode()
	{
		// ���C�����X�g�Ɉړ������񂪓��������X�g�̗v�f�����C�����X�g�Ɉړ�
		for (const auto& node : m_nextFrameAddNodeList)
		{
			m_componentList.push_front(node);
		}

		// �R�s�[���̃R���e�i�͍폜
		m_nextFrameAddNodeList.clear();
	}

	void GameObjectComponentList::removeDeadComponent()
	{
		// ���S�t���O�̗������R���|�[�l���g�����X�g����폜����
		m_componentList.remove_if([](const auto& node) { return node.isDead(); });
	}
}