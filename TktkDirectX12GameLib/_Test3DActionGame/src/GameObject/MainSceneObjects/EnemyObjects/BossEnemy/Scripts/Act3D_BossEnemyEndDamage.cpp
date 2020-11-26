#include "Act3D_BossEnemyEndDamage.h"

#include "../../../../../Enums/Enums.h"

void Act3D_BossEnemyEndDamage::onEnable()
{
	// タイマーを初期化
	m_endAttackSecTimer = EndDamageTimeSec;
}

void Act3D_BossEnemyEndDamage::update()
{
	if (m_endAttackSecTimer < 0.0f)
	{
		// ダメージ状態を無効にする
		getGameObject()->stateDisable(BossEnemyStateType::Damage);
		return;
	}

	// タイマーを更新する
	m_endAttackSecTimer -= tktk::DX12Game::deltaTime();
}
