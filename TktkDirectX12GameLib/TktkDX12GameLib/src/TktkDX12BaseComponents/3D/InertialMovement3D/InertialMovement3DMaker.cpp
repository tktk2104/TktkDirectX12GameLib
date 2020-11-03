#include "TktkDX12BaseComponents/3D/InertialMovement3D/InertialMovement3DMaker.h"

namespace tktk
{
	InertialMovement3DMaker InertialMovement3DMaker::m_self;

	InertialMovement3DMaker & InertialMovement3DMaker::makeStart(GameObjectPtr user)
	{
		// �ϐ�������������
		m_self = InertialMovement3DMaker();

		// �����̃��[�U�[��ݒ�
		m_self.m_user = user;

		// ���g�̎Q�Ƃ�Ԃ�
		return m_self;
	}

	InertialMovement3DMaker& InertialMovement3DMaker::makeStart(const StateTypeHierarchy& targetState, GameObjectPtr user)
	{
		// �ϐ�������������
		m_self = InertialMovement3DMaker();

		// �����̃��[�U�[��ݒ�
		m_self.m_user = user;

		// �����̒ǉ��K�w��ݒ�
		m_self.m_targetState = targetState;

		// ���g�̎Q�Ƃ�Ԃ�
		return m_self;
	}

	ComponentPtr<InertialMovement3D> InertialMovement3DMaker::craete()
	{
		// ���g��ǉ�����K�w��񂪋󂾂����畁�ʂɍ쐬����
		if (m_targetState.hierarchy.empty())
		{
			// �R���|�[�l���g���쐬���Ă��̃|�C���^��Ԃ�
			return m_user->createComponent<InertialMovement3D>(
				m_decelerationPerSec,
				m_initVelocity
				);
		}
		
		// �R���|�[�l���g���쐬����
		auto createComponent = m_user->createComponent<InertialMovement3D>(
			m_decelerationPerSec,
			m_initVelocity
			);

		// �쐬�����R���|�[�l���g�����̃X�e�[�g�ɒǉ�����
		m_user->setComponentToStateMachine(m_targetState, createComponent);

		// �쐬�����R���|�[�l���g�̃|�C���^��Ԃ�
		return createComponent;
	}

	InertialMovement3DMaker & InertialMovement3DMaker::decelerationPerSec(float value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_decelerationPerSec = value;
		return *this;
	}

	InertialMovement3DMaker & InertialMovement3DMaker::initVelocity(const tktkMath::Vector3 & value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_initVelocity = value;
		return *this;
	}
}