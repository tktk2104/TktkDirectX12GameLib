#include "Act3D_EnemyDeleteTimer.h"

void Act3D_EnemyDeleteTimer::update()
{
	m_deleteSecTimer += tktk::DX12Game::deltaTime();

	if (m_deleteSecTimer > DeleteTimeSec)
	{
		getGameObject()->destroy();
	}
}
