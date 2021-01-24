#include "Sht2D_PlayerMissileActiveTimer.h"

#include "../../../../../Enums/Enums.h"

Sht2D_PlayerMissileActiveTimer::Sht2D_PlayerMissileActiveTimer(float activeTimeSec)
	: m_activeTimeSec(activeTimeSec)
{
}

void Sht2D_PlayerMissileActiveTimer::update()
{
	if (m_activeSecTimer > m_activeTimeSec)
	{
		getGameObject()->stateEnable(PlayerMissileStateType::Active);
		getGameObject()->stateDisable(PlayerMissileStateType::Idle);
		return;
	}

	m_activeSecTimer += tktk::DX12Game::deltaTime();
}
