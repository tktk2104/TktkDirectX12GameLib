#include "Act3D_PlayerCollisionReaction.h"

#include "../../../../../Enums/Enums.h"

void Act3D_PlayerCollisionReaction::onCollisionEnter(const tktk::GameObjectPtr& other)
{
	if (other->containGameobjectTag(GameObjectTag::EnemyAttackRange))
	{
		getGameObject()->sendMessage(EventMessageType::Damage, 1);
	}
}
