#include "Sht2D_ExplosionScript.h"

Sht2D_ExplosionScript::Sht2D_ExplosionScript(float effectEndTimeSec)
	: m_effectEndTimeSec(effectEndTimeSec)
{
}

void Sht2D_ExplosionScript::update()
{
	if (m_effectEndSecTimer > m_effectEndTimeSec)
	{
		getGameObject()->destroy();
		return;
	}

	m_effectEndSecTimer += tktk::DX12Game::deltaTime();
}