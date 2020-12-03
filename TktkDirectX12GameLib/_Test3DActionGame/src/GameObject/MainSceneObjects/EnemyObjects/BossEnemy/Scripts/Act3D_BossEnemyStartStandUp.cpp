#include "Act3D_BossEnemyStartStandUp.h"

#include "../../../../../Enums/Enums.h"

void Act3D_BossEnemyStartStandUp::onEnable()
{
	// タイマーを初期化
	m_startStandUpSecTimer = StartStandUpTimeSec;
}

void Act3D_BossEnemyStartStandUp::update()
{
	// タイマーのカウントがゼロになっていたら
	if (m_startStandUpSecTimer < 0.0f)
	{
		// 起き上がり状態を有効にする
		getGameObject()->stateEnable(BossEnemyStateType::StandUp);

		// ダウン中状態を無効にする
		getGameObject()->stateDisable(BossEnemyStateType::CantMove);
		return;
	}

	// タイマーをカウントダウンする
	m_startStandUpSecTimer -= tktk::DX12Game::deltaTime();
}
