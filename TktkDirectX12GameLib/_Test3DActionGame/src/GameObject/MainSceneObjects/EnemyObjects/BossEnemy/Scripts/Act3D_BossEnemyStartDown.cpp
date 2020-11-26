#include "Act3D_BossEnemyStartDown.h"

#include "../../../../../Enums/Enums.h"

void Act3D_BossEnemyStartDown::onEnable()
{
	// タイマーを初期化
	m_startDownSecTimer = StartDownTimeSec;
}

void Act3D_BossEnemyStartDown::update()
{
	if (m_startDownSecTimer < 0.0f)
	{
		// ダウン中状態を有効にする
		getGameObject()->statesEnable({ BossEnemyStateType::Down, BossEnemyStateType::CantMove });

		// 通常、攻撃、失敗ローリング状態を無効にする
		getGameObject()->statesDisable({ BossEnemyStateType::Normal, BossEnemyStateType::Attack, BossEnemyStateType::MissRool });
		return;
	}

	// タイマーを更新する
	m_startDownSecTimer -= tktk::DX12Game::deltaTime();
}
