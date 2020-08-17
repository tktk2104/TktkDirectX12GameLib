#include "TktkDX12Game/Component/ComponentManager.h"

#include "TktkDX12Game/Component/ComponentMainList.h"

namespace tktk
{
	void ComponentManager::update()
	{
		// �O�t���[���ɒǉ����ꂽ�R���|�[�l���g�����C�����X�g�ɒǉ�����
		for (const auto& node : m_mainMap)
		{
			node.second->moveNewComponent();
		}
		m_startList.movePreFrameAddedNode();
		m_collisionList.movePreFrameAddedNode();
		m_drawList.movePreFrameAddedNode();

		// �A�N�e�B�u�t���O�̔���ƃt���O�ύX���̊֐��Ăяo������
		for (const auto& node : m_mainMap)
		{
			node.second->activeChangeCheck();
		}

		// �ustart()�v�֐��Ăяo������
		m_startList.runStartFunc();
		
		// �uupdate()�v�֐��Ăяo������
		for (const auto& node : m_mainMap)
		{
			node.second->runUpdate();
		}

		// �Փ˔���n�֐��Ăяo������
		m_collisionList.runCollisionFunc();

		// �uafterCollide()�v�֐��Ăяo������
		for (const auto& node : m_mainMap)
		{
			node.second->runAfterCollide();
		}
	}

	void ComponentManager::removeDeadComponent()
	{
		// ���C�����X�g���Ǘ����Ă���R���|�[�l���g�|�C���^�̐����m�F
		for (const auto& node : m_mainMap)
		{
			node.second->removeDeadComponent();
		}

		// �Փ˔��胊�X�g���Ǘ����Ă���R���|�[�l���g�|�C���^�̐����m�F
		m_collisionList.removeDeadComponent();

		// �`�惊�X�g���Ǘ����Ă���R���|�[�l���g�|�C���^�̐����m�F
		m_drawList.removeDeadComponent();
	}

	void ComponentManager::draw()
	{
		// �udraw()�v�֐��Ăяo������
		m_drawList.runDrawFunc();
	}

	void ComponentManager::addCollisionGroup(int firstGroup, int secondGroup)
	{
		// �Փ˔���̑g�ݍ��킹��ǉ�
		m_collisionList.addCollisionGroup(firstGroup, secondGroup);
	}
}