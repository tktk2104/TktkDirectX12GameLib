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
	// �^�C�}�[�̃J�E���g���[���ɂȂ��Ă�����
	if (m_endAttackSecTimer < 0.0f)
	{
		// �ړ���Ԃ�L���ɂ���
		getGameObject()->stateEnable(ShooterEnemyStateType::Move);

		// �U����Ԃ𖳌��ɂ���
		getGameObject()->statesDisable({ ShooterEnemyStateType::Attack, m_attackType });
		return;
	}

	// �^�C�}�[���J�E���g�_�E������
	m_endAttackSecTimer -= tktk::DX12Game::deltaTime();
}
