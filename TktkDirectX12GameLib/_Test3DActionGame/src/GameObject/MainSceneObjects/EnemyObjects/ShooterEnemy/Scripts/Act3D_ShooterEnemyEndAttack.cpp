#include "Act3D_ShooterEnemyEndAttack.h"

Act3D_ShooterEnemyEndAttack::Act3D_ShooterEnemyEndAttack(float endAttackTimeSec, ShooterEnemyStateType attackType)
	: m_endAttackTimeSec(endAttackTimeSec)
	, m_attackType(attackType)
{
}

void Act3D_ShooterEnemyEndAttack::onEnable()
{
	// タイマーを初期化
	m_endAttackSecTimer = m_endAttackTimeSec;
}

void Act3D_ShooterEnemyEndAttack::update()
{
	// タイマーのカウントがゼロになっていたら
	if (m_endAttackSecTimer < 0.0f)
	{
		// 移動状態を有効にする
		getGameObject()->stateEnable(ShooterEnemyStateType::Move);

		// 攻撃状態を無効にする
		getGameObject()->statesDisable({ ShooterEnemyStateType::Attack, m_attackType });
		return;
	}

	// タイマーをカウントダウンする
	m_endAttackSecTimer -= tktk::DX12Game::deltaTime();
}
