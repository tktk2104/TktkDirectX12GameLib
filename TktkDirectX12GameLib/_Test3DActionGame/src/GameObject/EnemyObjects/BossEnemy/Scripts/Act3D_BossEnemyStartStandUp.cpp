#include "Act3D_BossEnemyStartStandUp.h"

#include "../../../../Enums/Enums.h"

void Act3D_BossEnemyStartStandUp::onEnable()
{
	// タイマーを初期化
	m_startStandUpSecTimer = StartStandUpTimeSec;
}

void Act3D_BossEnemyStartStandUp::update()
{
	if (m_startStandUpSecTimer < 0.0f)
	{
		// 起き上がり状態を有効にする
		getGameObject()->stateEnable(BossEnemyStateType::StandUp);

		// ダウン中状態を無効にする
		getGameObject()->stateDisable(BossEnemyStateType::CantMove);
		return;
	}

	// タイマーを更新する
	m_startStandUpSecTimer -= tktk::DX12Game::deltaTime();
}
