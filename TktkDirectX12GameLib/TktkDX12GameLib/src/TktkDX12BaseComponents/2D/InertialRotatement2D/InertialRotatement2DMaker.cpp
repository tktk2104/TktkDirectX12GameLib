#include "TktkDX12BaseComponents/2D/InertialRotatement2D/InertialRotatement2DMaker.h"

namespace tktk
{
	InertialRotatement2DMaker InertialRotatement2DMaker::m_self;

	InertialRotatement2DMaker & InertialRotatement2DMaker::makeStart(GameObjectPtr user)
	{
		// �ϐ�������������
		m_self = InertialRotatement2DMaker();

		// �����̃��[�U�[��ݒ�
		m_self.m_user = user;

		// ���g�̎Q�Ƃ�Ԃ�
		return m_self;
	}

	ComponentPtr<InertialRotatement2D> InertialRotatement2DMaker::create()
	{
		// ���g��ǉ�����K�w��񂪋󂾂����畁�ʂɍ쐬����
		if (m_targetState.empty())
		{
			// �R���|�[�l���g���쐬���Ă��̃|�C���^��Ԃ�
			return m_user->createComponent<InertialRotatement2D>(
				m_decelerationPerSec,
				m_initVelocity
				);
		}

		// �R���|�[�l���g���쐬����
		auto createComponent = m_user->createComponent<InertialRotatement2D>(
			m_decelerationPerSec,
			m_initVelocity
			);

		// �쐬�����R���|�[�l���g�����̃X�e�[�g�ɒǉ�����
		m_user->setComponentToStateMachine(m_targetState, createComponent);

		// �쐬�����R���|�[�l���g�̃|�C���^��Ԃ�
		return createComponent;
	}

	InertialRotatement2DMaker & InertialRotatement2DMaker::decelerationPerSec(float value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_decelerationPerSec = value;
		return *this;
	}

	InertialRotatement2DMaker & InertialRotatement2DMaker::initVelocity(float value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_initVelocity = value;
		return *this;
	}
}