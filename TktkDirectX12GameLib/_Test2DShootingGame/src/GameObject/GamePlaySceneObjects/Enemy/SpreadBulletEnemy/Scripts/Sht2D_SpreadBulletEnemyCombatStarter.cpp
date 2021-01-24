#include "Sht2D_SpreadBulletEnemyCombatStarter.h"

#include "../../../../../Enums/Enums.h"

void Sht2D_SpreadBulletEnemyCombatStarter::start()
{
	m_transform = getComponent<tktk::Transform2D>();

	if (m_transform.expired())
	{
		throw std::runtime_error("Sht2D_SpreadBulletEnemyCombatStarter not found Transform2D");
	}
}

void Sht2D_SpreadBulletEnemyCombatStarter::update()
{
	if (m_transform->getWorldPosition().y > StartCombatYPos)
	{
		getGameObject()->stateDisable(SpreadBulletEnemyState::Entry);

		getGameObject()->stateEnable(SpreadBulletEnemyState::Combat);
	}
}
