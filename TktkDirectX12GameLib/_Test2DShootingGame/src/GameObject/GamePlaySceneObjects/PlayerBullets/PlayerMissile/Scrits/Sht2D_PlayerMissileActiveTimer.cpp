#include "Sht2D_PlayerMissileActiveTimer.h"

#include "../../../../../Enums/Enums.h"

Sht2D_PlayerMissileActiveTimer::Sht2D_PlayerMissileActiveTimer(float activeTimeSec)
	: m_activeSecTimer(activeTimeSec)
{
}

void Sht2D_PlayerMissileActiveTimer::update()
{
	// アクティブタイマーカウントが０だったら
	if (m_activeSecTimer < 0.0f)
	{
		// ミサイルのステートを待機状態からアクティブ状態に遷移して関数を終える
		getGameObject()->stateEnable(PlayerMissileStateType::Active);
		getGameObject()->stateDisable(PlayerMissileStateType::Idle);
		return;
	}

	// アクティブタイマーをカウントダウン
	m_activeSecTimer -= tktk::DX12Game::deltaTime();
}
