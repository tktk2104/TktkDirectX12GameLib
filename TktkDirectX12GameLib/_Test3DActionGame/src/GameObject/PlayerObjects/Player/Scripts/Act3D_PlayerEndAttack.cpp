#include "Act3D_PlayerEndAttack.h"

Act3D_PlayerEndAttack::Act3D_PlayerEndAttack(float endAttackTime, PlayerStateType attackType)
	: m_endAttackTimeSec(endAttackTime)
	, m_attackType(attackType)
{
}

void Act3D_PlayerEndAttack::onEnable()
{
	// タイマーを初期化
	m_endAttackSecTimer = m_endAttackTimeSec;
}

void Act3D_PlayerEndAttack::update()
{
	if (m_endAttackSecTimer < 0.0f)
	{
		// 通常状態を有効にする
		getGameObject()->stateEnable(PlayerStateType::Move);

		// 攻撃状態を無効にする
		getGameObject()->stateDisable(PlayerStateType::Attack);
		getGameObject()->stateDisable(m_attackType);
		return;
	}

	// タイマーを更新する
	m_endAttackSecTimer -= tktk::DX12Game::deltaTime();
}
