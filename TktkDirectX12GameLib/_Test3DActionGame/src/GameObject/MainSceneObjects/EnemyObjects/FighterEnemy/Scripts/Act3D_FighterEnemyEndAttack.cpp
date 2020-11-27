#include "Act3D_FighterEnemyEndAttack.h"

Act3D_FighterEnemyEndAttack::Act3D_FighterEnemyEndAttack(float endAttackTimeSec, FighterEnemyState attackType)
	: m_endAttackTimeSec(endAttackTimeSec)
	, m_attackType(attackType)
{
}

void Act3D_FighterEnemyEndAttack::onEnable()
{
	// �^�C�}�[��������
	m_endAttackSecTimer = m_endAttackTimeSec;
}

void Act3D_FighterEnemyEndAttack::update()
{
	// �^�C�}�[�̃J�E���g���[���ɂȂ��Ă�����
	if (m_endAttackSecTimer < 0.0f)
	{
		// ������Ԃ�L���ɂ���
		getGameObject()->statesEnable({ FighterEnemyState::Move, FighterEnemyState::Walk });

		// �U����Ԃ𖳌��ɂ���
		getGameObject()->statesDisable({ FighterEnemyState::Attack, m_attackType });
		return;
	}

	// �^�C�}�[���J�E���g�_�E������
	m_endAttackSecTimer -= tktk::DX12Game::deltaTime();
}
