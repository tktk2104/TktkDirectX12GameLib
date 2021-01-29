#include "Sht2D_PlayerBombActiveTimer.h"

#include "../../../../../Enums/Enums.h"

Sht2D_PlayerBombActiveTimer::Sht2D_PlayerBombActiveTimer(float activeTimeSec)
	: m_activeSecTimer(activeTimeSec)
{
}

void Sht2D_PlayerBombActiveTimer::update()
{
	// アクティブタイマーカウントが０以下だったら
	if (m_activeSecTimer < 0.0f)
	{
		// プレイヤーボムの状態を待機からアクティブへ遷移させ、関数を終える
		getGameObject()->stateEnable(PlayerBombStateType::Active);
		getGameObject()->stateDisable(PlayerBombStateType::Idle);
		return;
	}

	// アクティブタイマーをカウントダウンする
	m_activeSecTimer -= tktk::DX12Game::deltaTime();
}
