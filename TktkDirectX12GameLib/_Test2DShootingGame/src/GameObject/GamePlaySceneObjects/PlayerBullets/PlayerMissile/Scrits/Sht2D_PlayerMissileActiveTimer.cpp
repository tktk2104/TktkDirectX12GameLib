#include "Sht2D_PlayerMissileActiveTimer.h"

#include "../../../../../Enums/Enums.h"

Sht2D_PlayerMissileActiveTimer::Sht2D_PlayerMissileActiveTimer(float activeTimeSec)
	: m_activeSecTimer(activeTimeSec)
{
}

void Sht2D_PlayerMissileActiveTimer::update()
{
	// �A�N�e�B�u�^�C�}�[�J�E���g���O��������
	if (m_activeSecTimer < 0.0f)
	{
		// �~�T�C���̃X�e�[�g��ҋ@��Ԃ���A�N�e�B�u��ԂɑJ�ڂ��Ċ֐����I����
		getGameObject()->stateEnable(PlayerMissileStateType::Active);
		getGameObject()->stateDisable(PlayerMissileStateType::Idle);
		return;
	}

	// �A�N�e�B�u�^�C�}�[���J�E���g�_�E��
	m_activeSecTimer -= tktk::DX12Game::deltaTime();
}
