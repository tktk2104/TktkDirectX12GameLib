#include "Act3D_SelfDeadTimer.h"

Act3D_SelfDeadTimer::Act3D_SelfDeadTimer(float deadTimeSec)
	: m_deadTimeSec(deadTimeSec)
{
}

void Act3D_SelfDeadTimer::start()
{
	// �^�C�}�[��������
	m_deadSecTimer = m_deadTimeSec;
}

void Act3D_SelfDeadTimer::update()
{
	// �^�C�}�[�̃J�E���g���[���ɂȂ�����
	if (m_deadSecTimer < 0.0f)
	{
		// ���̃R���|�[�l���g�̏����҂��E��
		getGameObject()->destroy();
		return;
	}

	// �^�C�}�[���J�E���g�_�E��
	m_deadSecTimer -= tktk::DX12Game::deltaTime();
}
