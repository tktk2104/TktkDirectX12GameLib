#include "Act3D_FighterEnemyStartRun.h"

#include "../../../../../Enums/Enums.h"

void Act3D_FighterEnemyStartRun::onEnable()
{
	// タイマーを初期化
	m_startRunSecTimer = StartRunTimeSec;
}

void Act3D_FighterEnemyStartRun::update()
{
	// タイマーのカウントがゼロになっていたら
	if (m_startRunSecTimer < 0.0f)
	{
		// 走り状態を有効にする
		getGameObject()->stateEnable(FighterEnemyState::Run);

		// 歩き状態を無効にする
		getGameObject()->stateDisable(FighterEnemyState::Walk);
		return;
	}

	// タイマーをカウントダウンする
	m_startRunSecTimer -= tktk::DX12Game::deltaTime();
}
