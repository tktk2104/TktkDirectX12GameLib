#include "Act3D_InputToStartComboAttack.h"

#include "../../../../../Enums/Enums.h"

void Act3D_InputToStartComboAttack::onEnable()
{
	m_invalidStateChangeSecTimer = 0.0f;
	m_afterInput = false;
}

void Act3D_InputToStartComboAttack::update()
{
	// 攻撃ボタンが押されたら
	if (tktk::DX12Game::isTrigger(CommandId::Attack))
	{
		m_afterInput = true;
	}

	if (m_invalidStateChangeSecTimer < InvalidStateChangeTimeSec)
	{
		m_invalidStateChangeSecTimer += tktk::DX12Game::deltaTime();
		return;
	}

	if (m_afterInput)
	{
		// 攻撃（一段）状態を切る
		getGameObject()->stateDisable(PlayerStateType::Attack1);

		// 攻撃（二段）状態にする
		getGameObject()->stateEnable(PlayerStateType::Attack2);
	}
}
