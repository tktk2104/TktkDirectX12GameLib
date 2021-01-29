#include "Sht2D_PlayerBombActiveTimer.h"

#include "../../../../../Enums/Enums.h"

Sht2D_PlayerBombActiveTimer::Sht2D_PlayerBombActiveTimer(float activeTimeSec)
	: m_activeSecTimer(activeTimeSec)
{
}

void Sht2D_PlayerBombActiveTimer::update()
{
	// �A�N�e�B�u�^�C�}�[�J�E���g���O�ȉ���������
	if (m_activeSecTimer < 0.0f)
	{
		// �v���C���[�{���̏�Ԃ�ҋ@����A�N�e�B�u�֑J�ڂ����A�֐����I����
		getGameObject()->stateEnable(PlayerBombStateType::Active);
		getGameObject()->stateDisable(PlayerBombStateType::Idle);
		return;
	}

	// �A�N�e�B�u�^�C�}�[���J�E���g�_�E������
	m_activeSecTimer -= tktk::DX12Game::deltaTime();
}
