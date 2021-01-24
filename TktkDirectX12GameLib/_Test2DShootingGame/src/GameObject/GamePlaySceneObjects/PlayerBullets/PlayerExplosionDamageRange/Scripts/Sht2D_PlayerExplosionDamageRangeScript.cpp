#include "Sht2D_PlayerExplosionDamageRangeScript.h"

Sht2D_PlayerExplosionDamageRangeScript::Sht2D_PlayerExplosionDamageRangeScript(float deadTimeSec)
	: m_deadTimeSec(deadTimeSec)
{
}

void Sht2D_PlayerExplosionDamageRangeScript::update()
{
	if (m_deadSecTimer > m_deadTimeSec)
	{
		getGameObject()->destroy();
		return;
	}

	m_deadSecTimer += tktk::DX12Game::deltaTime();
}
