#include "TktkDX12BaseComponents/2D/InertialMovement2D/InertialMovement2DMaker.h"

namespace tktk
{
	InertialMovement2DMaker InertialMovement2DMaker::m_self;

	InertialMovement2DMaker & InertialMovement2DMaker::makeStart(GameObjectPtr user)
	{
		// �ϐ�������������
		m_self = InertialMovement2DMaker();

		// �����̃��[�U�[��ݒ�
		m_self.m_user = user;

		// ���g�̎Q�Ƃ�Ԃ�
		return m_self;
	}

	InertialMovement2DMaker& InertialMovement2DMaker::makeStart(const StateTypeHierarchy& targetState, GameObjectPtr user)
	{
		// �ϐ�������������
		m_self = InertialMovement2DMaker();

		// �����̃��[�U�[��ݒ�
		m_self.m_user = user;

		// �����̒ǉ��K�w��ݒ�
		m_self.m_targetState = targetState;

		// ���g�̎Q�Ƃ�Ԃ�
		return m_self;
	}

	ComponentPtr<InertialMovement2D> InertialMovement2DMaker::create()
	{
		// ���g��ǉ�����K�w��񂪋󂾂����畁�ʂɍ쐬����
		if (m_targetState.hierarchy.empty())
		{
			// �R���|�[�l���g���쐬���Ă��̃|�C���^��Ԃ�
			return m_user->createComponent<InertialMovement2D>(
				m_decelerationPerSec,
				m_initVelocity
				);
		}

		// �R���|�[�l���g���쐬����
		auto createComponent = m_user->createComponent<InertialMovement2D>(
			m_decelerationPerSec,
			m_initVelocity
			);

		// �쐬�����R���|�[�l���g�����̃X�e�[�g�ɒǉ�����
		m_user->setComponentToStateMachine(m_targetState, createComponent);

		// �쐬�����R���|�[�l���g�̃|�C���^��Ԃ�
		return createComponent;
	}

	InertialMovement2DMaker & InertialMovement2DMaker::decelerationPerSec(float value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_decelerationPerSec = value;
		return *this;
	}

	InertialMovement2DMaker & InertialMovement2DMaker::initVelocity(const tktkMath::Vector2 & value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_initVelocity = value;
		return *this;
	}
}