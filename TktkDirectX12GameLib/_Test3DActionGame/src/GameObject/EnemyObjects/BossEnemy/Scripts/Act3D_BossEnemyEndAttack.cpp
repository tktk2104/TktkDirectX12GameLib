#include "Act3D_BossEnemyEndAttack.h"

Act3D_BossEnemyEndAttack::Act3D_BossEnemyEndAttack(float endAttackTimeSec, BossEnemyStateType attackType)
	: m_endAttackTimeSec(endAttackTimeSec)
	, m_attackType(attackType)
{
}

void Act3D_BossEnemyEndAttack::onEnable()
{
	// タイマーを初期化
	m_endAttackSecTimer = m_endAttackTimeSec;
}

void Act3D_BossEnemyEndAttack::update()
{
	if (m_endAttackSecTimer < 0.0f)
	{
		// 移動状態を有効にする
		getGameObject()->stateEnable(BossEnemyStateType::Move);

		// 攻撃状態を無効にする
		getGameObject()->statesDisable({ BossEnemyStateType::Attack, m_attackType });
		return;
	}

	// タイマーを更新する
	m_endAttackSecTimer -= tktk::DX12Game::deltaTime();
}
