#include "TktkDX12BaseComponents/3D/SphereCollider/SphereColliderMaker.h"

namespace tktk
{
	SphereColliderMaker SphereColliderMaker::m_self;

	SphereColliderMaker& SphereColliderMaker::makeStart(GameObjectPtr user)
	{
		// �ϐ�������������
		m_self = SphereColliderMaker();

		// �����̃��[�U�[��ݒ�
		m_self.m_user = user;

		// ���g�̎Q�Ƃ�Ԃ�
		return m_self;
	}

	ComponentPtr<SphereCollider>SphereColliderMaker::create()
	{
		// ���g��ǉ�����K�w��񂪋󂾂����畁�ʂɍ쐬����
		if (m_targetState.empty())
		{
			// �R���|�[�l���g���쐬���Ă��̃|�C���^��Ԃ�
			return m_user->createComponent<SphereCollider>(
				m_collisionGroupType,
				m_radius,
				m_localPosition,
				m_isExtrude,
				m_extrudedRate
				);
		}

		// �R���|�[�l���g���쐬����
		auto createComponent = m_user->createComponent<SphereCollider>(
			m_collisionGroupType,
			m_radius,
			m_localPosition,
			m_isExtrude,
			m_extrudedRate
			);

		// �쐬�����R���|�[�l���g�����̃X�e�[�g�ɒǉ�����
		m_user->setComponentToStateMachine(m_targetState, createComponent);

		// �쐬�����R���|�[�l���g�̃|�C���^��Ԃ�
		return createComponent;
	}

	SphereColliderMaker& SphereColliderMaker::radius(float value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_radius = value;
		return *this;
	}

	SphereColliderMaker& SphereColliderMaker::localPosition(const tktkMath::Vector3& value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_localPosition = value;
		return *this;
	}

	SphereColliderMaker& SphereColliderMaker::isExtrude(bool value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_isExtrude = value;
		return *this;
	}

	SphereColliderMaker& SphereColliderMaker::extrudedRate(float value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_extrudedRate = value;
		return *this;
	}

	SphereColliderMaker& SphereColliderMaker::collisionGroupTypeImpl(int value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_collisionGroupType = value;
		return *this;
	}
}