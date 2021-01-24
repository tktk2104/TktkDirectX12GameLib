#include "Sht2D_PlayerMissileCollisionReaction.h"

#include "../../../../../Enums/Enums.h"

void Sht2D_PlayerMissileCollisionReaction::start()
{
	m_playerMissileExplode = getComponent<Sht2D_PlayerMissileExplode>();

	if (m_playerMissileExplode.expired())
	{
		throw std::runtime_error("Sht2D_PlayerMissileCollisionReaction not found Sht2D_PlayerMissileExplode");
	}
}

void Sht2D_PlayerMissileCollisionReaction::onCollisionEnter(const tktk::GameObjectPtr& other)
{
	// 衝突相手が敵だったら
	if (other->containGameobjectTag(GameObjectTag::Enemy))
	{
		// 起爆！！！
		m_playerMissileExplode->explode();
	}
}
