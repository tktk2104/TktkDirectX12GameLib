#include "Act3D_InputToStartComboAttack.h"

#include "../../../../Enums/Enums.h"

Act3D_InputToStartComboAttack::Act3D_InputToStartComboAttack(float invalidInputTimeSec)
	: m_invalidInputTimeSec(invalidInputTimeSec)
{
}

void Act3D_InputToStartComboAttack::onEnable()
{
	m_invalidInputSecTimer = 0.0f;
}

void Act3D_InputToStartComboAttack::update()
{
	if (m_invalidInputSecTimer < m_invalidInputTimeSec)
	{
		m_invalidInputSecTimer += tktk::DX12Game::deltaTime();
		return;
	}

	if (tktk::DX12Game::isTrigger(tktk::KeybordKeyType::key_Space))
	{
		// 攻撃（一段）状態を切る
		getGameObject()->stateDisable(PlayerStateType::Attack1);

		// 攻撃（二段）状態にする
		getGameObject()->stateEnable(PlayerStateType::Attack2);
	}
}
