#include "Act3D_FighterEnemyEndAttack.h"

Act3D_FighterEnemyEndAttack::Act3D_FighterEnemyEndAttack(float endAttackTimeSec, FighterEnemyState attackType)
	: m_endAttackTimeSec(endAttackTimeSec)
	, m_attackType(attackType)
{
}

void Act3D_FighterEnemyEndAttack::onEnable()
{
	// タイマーを初期化
	m_endAttackSecTimer = m_endAttackTimeSec;
}

void Act3D_FighterEnemyEndAttack::update()
{
	// タイマーのカウントがゼロになっていたら
	if (m_endAttackSecTimer < 0.0f)
	{
		// 歩き状態を有効にする
		getGameObject()->statesEnable({ FighterEnemyState::Move, FighterEnemyState::Walk });

		// 攻撃状態を無効にする
		getGameObject()->statesDisable({ FighterEnemyState::Attack, m_attackType });
		return;
	}

	// タイマーをカウントダウンする
	m_endAttackSecTimer -= tktk::DX12Game::deltaTime();
}
