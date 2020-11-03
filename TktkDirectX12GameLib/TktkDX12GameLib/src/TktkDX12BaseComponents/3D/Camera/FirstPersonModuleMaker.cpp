#include"TktkDX12BaseComponents/3D/Camera/FirstPersonModuleMaker.h"

namespace tktk
{
	FirstPersonModuleMaker FirstPersonModuleMaker::m_self;

	FirstPersonModuleMaker & FirstPersonModuleMaker::makeStart(GameObjectPtr user)
	{
		// �ϐ�������������
		m_self = FirstPersonModuleMaker();

		// �����̃��[�U�[��ݒ�
		m_self.m_user = user;

		// ���g�̎Q�Ƃ�Ԃ�
		return m_self;
	}

	FirstPersonModuleMaker& FirstPersonModuleMaker::makeStart(const StateTypeHierarchy& targetState, GameObjectPtr user)
	{
		// �ϐ�������������
		m_self = FirstPersonModuleMaker();

		// �����̃��[�U�[��ݒ�
		m_self.m_user = user;

		// �����̒ǉ��K�w��ݒ�
		m_self.m_targetState = targetState;

		// ���g�̎Q�Ƃ�Ԃ�
		return m_self;
	}

	ComponentPtr<FirstPersonModule> FirstPersonModuleMaker::create()
	{
		// ���g��ǉ�����K�w��񂪋󂾂����畁�ʂɍ쐬����
		if (m_targetState.hierarchy.empty())
		{
			return m_user->createComponent<FirstPersonModule>(
				m_rotateDegSpeedPerSec,
				m_moveSpeedPerSec,
				m_alwaysMoveForward,
				m_enableUpDownKey
				);
		}

		// �R���|�[�l���g���쐬����
		auto createComponent = m_user->createComponent<FirstPersonModule>(
			m_rotateDegSpeedPerSec,
			m_moveSpeedPerSec,
			m_alwaysMoveForward,
			m_enableUpDownKey
			);

		// �쐬�����R���|�[�l���g�����̃X�e�[�g�ɒǉ�����
		m_user->setComponentToStateMachine(m_targetState, createComponent);

		// �쐬�����R���|�[�l���g�̃|�C���^��Ԃ�
		return createComponent;
	}

	FirstPersonModuleMaker & FirstPersonModuleMaker::rotateDegSpeedPerSec(float value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_rotateDegSpeedPerSec = value;
		return *this;
	}

	FirstPersonModuleMaker & FirstPersonModuleMaker::moveSpeedPerSec(float value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_moveSpeedPerSec = value;
		return *this;
	}

	FirstPersonModuleMaker & FirstPersonModuleMaker::alwaysMoveForward(bool value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_alwaysMoveForward = value;
		return *this;
	}

	FirstPersonModuleMaker & FirstPersonModuleMaker::enableUpDownKey(bool value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_enableUpDownKey = value;
		return *this;
	}
}