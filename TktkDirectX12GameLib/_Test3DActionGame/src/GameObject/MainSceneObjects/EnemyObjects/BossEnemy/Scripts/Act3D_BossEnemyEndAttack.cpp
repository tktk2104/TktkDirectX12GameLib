#include "Act3D_BossEnemyEndAttack.h"

Act3D_BossEnemyEndAttack::Act3D_BossEnemyEndAttack(float endAttackTimeSec, BossEnemyStateType attackType)
	: m_endAttackTimeSec(endAttackTimeSec)
	, m_attackType(attackType)
{
}

void Act3D_BossEnemyEndAttack::onEnable()
{
	// �^�C�}�[��������
	m_endAttackSecTimer = m_endAttackTimeSec;
}

void Act3D_BossEnemyEndAttack::update()
{
	if (m_endAttackSecTimer < 0.0f)
	{
		// �ړ���Ԃ�L���ɂ���
		getGameObject()->stateEnable(BossEnemyStateType::Move);

		// �U����Ԃ𖳌��ɂ���
		getGameObject()->statesDisable({ BossEnemyStateType::Attack, m_attackType });
		return;
	}

	// �^�C�}�[���X�V����
	m_endAttackSecTimer -= tktk::DX12Game::deltaTime();
}
