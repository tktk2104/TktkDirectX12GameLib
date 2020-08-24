#include "TktkDX12Game/Component/ComponentCollisionFunc/ComponentCollisionFuncRunner.h"

#include <algorithm>
#include "TktkDX12Game/Component/ComponentBase.h"

namespace tktk
{
	void ComponentCollisionFuncRunner::updateHitObjectList()
	{
		// �O�t���[���̏Փ˔��茋�ʂ��X�V���āA���݂̏Փ˔��茋�ʂ�����������
		m_preHitObjectList = std::move(m_curHitObjectList);
		m_curHitObjectList.clear();
	}

	void ComponentCollisionFuncRunner::runCollideFunc(const ComponentCollisionFuncRunner& other)
	{
		// ���g���Փˑ���ǂ��炩������ł��邩�A��A�N�e�B�u��ԂɂȂ��Ă����牽�����Ȃ�
		if (m_selfPtr.isDead() || other.m_selfPtr.isDead() || !m_selfPtr->isActive() || !other.m_selfPtr->isActive()) return;

		// �Փ˔���֐����Ă�
		if (m_vtablePtr->runIsCollide(m_selfPtr, other.m_selfPtr))
		{
			// �Փˑ���̏������t���[���ł̏Փˑ��胊�X�g�ɒǉ�����
			m_curHitObjectList.push_front({ other.m_vtablePtr, other.m_selfPtr });

			// �O�t���[���ŏՓ˂��Ă������H
			bool isPreFrameHit = false;

			// �O�t���[���ł̏Փˑ��胊�X�g�����񂷂�
			for (const auto& preHitObject : m_preHitObjectList)
			{
				// �Փˑ���̃R���|�[�l���g�|�C���^�Ə��񒆂̏Փˑ���R���|�[�l���g�|�C���^��������������
				if (preHitObject.selfPtr.isSame(other.m_selfPtr))
				{
					// �O�t���[���Փ˃t���O�𗧂ĂāA���[�v���I������
					isPreFrameHit = true;
					break;
				}
			}

			// �O�t���[�����Փ˂��Ă�����
			if (isPreFrameHit)
			{
				// ���g�̃R���|�[�l���g����������Q�[���I�u�W�F�N�g�̏Փ˒��������Ă�
				m_selfPtr->getGameObject()->runOnCollisionStayAll(other.m_selfPtr->getGameObject());

				// �Փˑ���̃R���|�[�l���g����������Q�[���I�u�W�F�N�g�̏Փ˒��������Ă�
				other.m_selfPtr->getGameObject()->runOnCollisionStayAll(m_selfPtr->getGameObject());
			}
			// �O�t���[���͏Փ˂��Ă��Ȃ�������
			else
			{
				// ���g�̃R���|�[�l���g����������Q�[���I�u�W�F�N�g�̏ՓˊJ�n�������Ă�
				m_selfPtr->getGameObject()->runOnCollisionEnterAll(other.m_selfPtr->getGameObject());

				// �Փˑ���̃R���|�[�l���g����������Q�[���I�u�W�F�N�g�̏ՓˊJ�n�������Ă�
				other.m_selfPtr->getGameObject()->runOnCollisionEnterAll(m_selfPtr->getGameObject());
			}
		}
		// �Փ˂��Ă��Ȃ�������
		else
		{
			// �O�t���[���ŏՓ˂��Ă������H
			bool preFrameHit = false;

			// �O�t���[���ł̏Փˑ��胊�X�g�����񂷂�
			for (const auto& node : m_preHitObjectList)
			{
				// �Փˑ���̃R���|�[�l���g�|�C���^�Ə��񒆂̏Փˑ���R���|�[�l���g�|�C���^��������������
				if (node.selfPtr.isSame(other.m_selfPtr))
				{
					// �O�t���[���Փ˃t���O�𗧂ĂāA���[�v���I������
					preFrameHit = true;
					break;
				}
			}

			// �O�t���[���ŏՓ˂��Ă�����
			if (preFrameHit)
			{
				// ���g�̃R���|�[�l���g����������Q�[���I�u�W�F�N�g�̏ՓˏI���������Ă�
				m_selfPtr->getGameObject()->runOnCollisionExitAll(other.m_selfPtr->getGameObject());

				// �Փˑ���̃R���|�[�l���g����������Q�[���I�u�W�F�N�g�̏ՓˏI���������Ă�
				other.m_selfPtr->getGameObject()->runOnCollisionExitAll(m_selfPtr->getGameObject());
			}
		}
	}

	bool ComponentCollisionFuncRunner::isDead() const
	{
		return m_selfPtr.isDead();
	}

	ComponentCollisionFuncRunner::HitObject::HitObject(VTable* vtablePtr, ComponentBasePtr selfPtr)
		: vtablePtr(vtablePtr)
		, selfPtr(selfPtr) {}
}