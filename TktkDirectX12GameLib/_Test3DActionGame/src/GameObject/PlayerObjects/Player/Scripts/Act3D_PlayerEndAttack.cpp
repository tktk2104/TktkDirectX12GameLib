#include "Act3D_PlayerEndAttack.h"

Act3D_PlayerEndAttack::Act3D_PlayerEndAttack(float endAttackTime, PlayerStateType attackType)
	: m_endAttackTimeSec(endAttackTime)
	, m_attackType(attackType)
{
}

void Act3D_PlayerEndAttack::onEnable()
{
	// �^�C�}�[��������
	m_endAttackSecTimer = m_endAttackTimeSec;
}

void Act3D_PlayerEndAttack::update()
{
	if (m_endAttackSecTimer < 0.0f)
	{
		// �ʏ��Ԃ�L���ɂ���
		getGameObject()->stateEnable(PlayerStateType::Move);

		// �U����Ԃ𖳌��ɂ���
		getGameObject()->stateDisable(PlayerStateType::Attack);
		getGameObject()->stateDisable(m_attackType);
		return;
	}

	// �^�C�}�[���X�V����
	m_endAttackSecTimer -= tktk::DX12Game::deltaTime();
}
