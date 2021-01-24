#include "Sht2D_PlayerBombActiveTimer.h"

#include "../../../../../Enums/Enums.h"

Sht2D_PlayerBombActiveTimer::Sht2D_PlayerBombActiveTimer(float activeTimeSec)
	: m_activeTimeSec(activeTimeSec)
{
}

void Sht2D_PlayerBombActiveTimer::update()
{
	if (m_activeSecTimer > m_activeTimeSec)
	{
		getGameObject()->stateEnable(PlayerBombStateType::Active);
		getGameObject()->stateDisable(PlayerBombStateType::Idle);
		return;
	}

	m_activeSecTimer += tktk::DX12Game::deltaTime();
}
