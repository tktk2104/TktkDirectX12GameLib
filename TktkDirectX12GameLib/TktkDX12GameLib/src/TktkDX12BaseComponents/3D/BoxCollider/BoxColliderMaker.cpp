#include "TktkDX12BaseComponents/3D/BoxCollider/BoxColliderMaker.h"

namespace tktk
{
	BoxColliderMaker BoxColliderMaker::m_self;

	BoxColliderMaker& BoxColliderMaker::makeStart(GameObjectPtr user)
	{
		// �ϐ�������������
		m_self = BoxColliderMaker();

		// �����̃��[�U�[��ݒ�
		m_self.m_user = user;

		// ���g�̎Q�Ƃ�Ԃ�
		return m_self;
	}

	BoxColliderMaker& BoxColliderMaker::makeStart(const StateTypeHierarchy& targetState, GameObjectPtr user)
	{
		// �ϐ�������������
		m_self = BoxColliderMaker();

		// �����̃��[�U�[��ݒ�
		m_self.m_user = user;

		// �����̒ǉ��K�w��ݒ�
		m_self.m_targetState = targetState;

		// ���g�̎Q�Ƃ�Ԃ�
		return m_self;
	}

	ComponentPtr<BoxCollider> BoxColliderMaker::create()
	{
		// ���g��ǉ�����K�w��񂪋󂾂����畁�ʂɍ쐬����
		if (m_targetState.hierarchy.empty())
		{
			// �R���|�[�l���g���쐬���Ă��̃|�C���^��Ԃ�
			return m_user->createComponent<BoxCollider>(
				m_collisionGroupType,
				m_boxSize,
				m_localPosition,
				m_isExtrude,
				m_extrudedRate
				);
		}
		
		// �R���|�[�l���g���쐬����
		auto createComponent = m_user->createComponent<BoxCollider>(
			m_collisionGroupType,
			m_boxSize,
			m_localPosition,
			m_isExtrude,
			m_extrudedRate
			);

		// �쐬�����R���|�[�l���g�����̃X�e�[�g�ɒǉ�����
		m_user->setComponentToStateMachine(m_targetState, createComponent);

		// �쐬�����R���|�[�l���g�̃|�C���^��Ԃ�
		return createComponent;
	}

	BoxColliderMaker& BoxColliderMaker::collisionGroupType(CollisionGroupTypeCarrier value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_collisionGroupType = value;
		return *this;
	}

	BoxColliderMaker& BoxColliderMaker::boxSize(const tktkMath::Vector3& value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_boxSize = value;
		return *this;
	}

	BoxColliderMaker& BoxColliderMaker::localPosition(const tktkMath::Vector3& value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_localPosition = value;
		return *this;
	}

	BoxColliderMaker& BoxColliderMaker::isExtrude(bool value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_isExtrude = value;
		return *this;
	}

	BoxColliderMaker& BoxColliderMaker::extrudedRate(float value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_extrudedRate = value;
		return *this;
	}
}