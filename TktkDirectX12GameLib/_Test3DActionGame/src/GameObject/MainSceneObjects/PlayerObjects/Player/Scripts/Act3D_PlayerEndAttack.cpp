#include "Act3D_PlayerEndAttack.h"

Act3D_PlayerEndAttack::Act3D_PlayerEndAttack(float endAttackTime)
	: m_endAttackTimeSec(endAttackTime)
{
}

void Act3D_PlayerEndAttack::onEnable()
{
	// タイマーを初期化
	m_endAttackSecTimer = m_endAttackTimeSec;
}

void Act3D_PlayerEndAttack::update()
{
	// タイマーのカウントがゼロだったら
	if (m_endAttackSecTimer < 0.0f)
	{
		// 通常状態を有効にする
		getGameObject()->stateEnable(PlayerStateType::Move);

		// 攻撃系状態を無効にする
		getGameObject()->statesDisable({ PlayerStateType::Attack, PlayerStateType::Attack1, PlayerStateType::Attack2, PlayerStateType::JumpAttack });
		return;
	}

	// タイマーをカウントダウンする
	m_endAttackSecTimer -= tktk::DX12Game::deltaTime();
}
