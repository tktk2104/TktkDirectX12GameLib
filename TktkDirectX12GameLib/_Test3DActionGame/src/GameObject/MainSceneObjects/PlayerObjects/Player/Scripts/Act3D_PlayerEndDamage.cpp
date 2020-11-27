#include "Act3D_PlayerEndDamage.h"

#include "../../../../../Enums/Enums.h"

void Act3D_PlayerEndDamage::onEnable()
{
	// タイマーを初期化
	m_endDamageSecTimer = EndDamageTimeSec;
}

void Act3D_PlayerEndDamage::update()
{
	// タイマーのカウントがゼロだったら
	if (m_endDamageSecTimer < 0.0f)
	{
		// 通常状態を有効にする
		getGameObject()->stateEnable(PlayerStateType::Normal);

		// ダメージ状態を無効にする
		getGameObject()->stateDisable(PlayerStateType::Damage);
		return;
	}

	// タイマーをカウントダウンする
	m_endDamageSecTimer -= tktk::DX12Game::deltaTime();
}
