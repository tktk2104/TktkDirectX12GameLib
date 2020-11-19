#include "Act3D_BossEnemyEndDown.h"

#include "../../../../Enums/Enums.h"

void Act3D_BossEnemyEndDown::onEnable()
{
	// タイマーを初期化
	m_endDownUpSecTimer = EndDownTimeSec;
}

void Act3D_BossEnemyEndDown::update()
{
	if (m_endDownUpSecTimer < 0.0f)
	{
		// 通常、移動状態を有効にする
		getGameObject()->statesEnable({ BossEnemyStateType::Normal, BossEnemyStateType::Move });

		// ダウン中状態を無効にする
		getGameObject()->statesDisable({ BossEnemyStateType::Down, BossEnemyStateType::StandUp });
		return;
	}

	// タイマーを更新する
	m_endDownUpSecTimer -= tktk::DX12Game::deltaTime();
}
