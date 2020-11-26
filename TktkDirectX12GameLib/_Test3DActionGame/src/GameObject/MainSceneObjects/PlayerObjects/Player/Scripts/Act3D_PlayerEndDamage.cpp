#include "Act3D_PlayerEndDamage.h"

#include "../../../../../Enums/Enums.h"

void Act3D_PlayerEndDamage::onEnable()
{
	// タイマーを初期化
	m_endDamageSecTimer = EndDamageTimeSec;
}

void Act3D_PlayerEndDamage::update()
{
	if (m_endDamageSecTimer < 0.0f)
	{
		// 通常状態を有効にする
		getGameObject()->stateEnable(PlayerStateType::Normal);

		// ダメージ状態を無効にする
		getGameObject()->stateDisable(PlayerStateType::Damage);
		return;
	}

	// タイマーを更新する
	m_endDamageSecTimer -= tktk::DX12Game::deltaTime();
}
