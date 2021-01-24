#include "Sht2D_PlayerBombCollisionReaction.h"

#include "../../../../../Enums/Enums.h"

void Sht2D_PlayerBombCollisionReaction::start()
{
	m_playerBombExplode = getComponent<Sht2D_PlayerBombExplode>();

	if (m_playerBombExplode.expired())
	{
		throw std::runtime_error("Sht2D_PlayerBombCollisionReaction not found Sht2D_PlayerBombExplode");
	}
}

void Sht2D_PlayerBombCollisionReaction::onCollisionEnter(const tktk::GameObjectPtr& other)
{
	// 衝突相手が敵だったら
	if (other->containGameobjectTag(GameObjectTag::Enemy))
	{
		// 起爆！！！
		m_playerBombExplode->explode();
	}
}