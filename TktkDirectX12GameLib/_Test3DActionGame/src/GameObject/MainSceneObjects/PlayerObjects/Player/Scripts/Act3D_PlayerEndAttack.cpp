#include "Act3D_PlayerEndAttack.h"

Act3D_PlayerEndAttack::Act3D_PlayerEndAttack(float endAttackTime)
	: m_endAttackTimeSec(endAttackTime)
{
}

void Act3D_PlayerEndAttack::onEnable()
{
	// �^�C�}�[��������
	m_endAttackSecTimer = m_endAttackTimeSec;
}

void Act3D_PlayerEndAttack::update()
{
	// �^�C�}�[�̃J�E���g���[����������
	if (m_endAttackSecTimer < 0.0f)
	{
		// �ʏ��Ԃ�L���ɂ���
		getGameObject()->stateEnable(PlayerStateType::Move);

		// �U���n��Ԃ𖳌��ɂ���
		getGameObject()->statesDisable({ PlayerStateType::Attack, PlayerStateType::Attack1, PlayerStateType::Attack2, PlayerStateType::JumpAttack });
		return;
	}

	// �^�C�}�[���J�E���g�_�E������
	m_endAttackSecTimer -= tktk::DX12Game::deltaTime();
}
