#include "Act3D_FighterEnemyStartComboAttack.h"

#include "../../../../../Enums/Enums.h"

void Act3D_FighterEnemyStartComboAttack::onEnable()
{
	// タイマーを初期化
	m_startComboSecTimer = StartComboTimeSec;
}

void Act3D_FighterEnemyStartComboAttack::update()
{
	if (m_startComboSecTimer < 0.0f)
	{
		// スワイプ攻撃状態を有効にする
		getGameObject()->stateEnable(FighterEnemyState::Swiping);

		// パンチ攻撃状態を無効にする
		getGameObject()->stateDisable(FighterEnemyState::Punch);
		return;
	}

	// タイマーを更新する
	m_startComboSecTimer -= tktk::DX12Game::deltaTime();
}
