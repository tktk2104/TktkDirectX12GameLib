#include "Act3D_ShooterEnemyEndAttack.h"

Act3D_ShooterEnemyEndAttack::Act3D_ShooterEnemyEndAttack(float endAttackTimeSec, ShooterEnemyStateType attackType)
	: m_endAttackTimeSec(endAttackTimeSec)
	, m_attackType(attackType)
{
}

void Act3D_ShooterEnemyEndAttack::onEnable()
{
	// �^�C�}�[��������
	m_endAttackSecTimer = m_endAttackTimeSec;
}

void Act3D_ShooterEnemyEndAttack::update()
{
	if (m_endAttackSecTimer < 0.0f)
	{
		// �ړ���Ԃ�L���ɂ���
		getGameObject()->stateEnable(ShooterEnemyStateType::Move);

		// �U����Ԃ𖳌��ɂ���
		getGameObject()->stateDisable(ShooterEnemyStateType::Attack);
		getGameObject()->stateDisable(m_attackType);
		return;
	}

	// �^�C�}�[���X�V����
	m_endAttackSecTimer -= tktk::DX12Game::deltaTime();
}
