#include "Act3D_EnemyCollisionReaction.h"

#include "../../../../Enums/Enums.h"

void Act3D_EnemyCollisionReaction::onCollisionEnter(const tktk::GameObjectPtr& other)
{
	if (other->containGameobjectTag(GameObjectTag::PlayerAttackRange))
	{
  		getGameObject()->sendMessage(EventMessageType::Damage, 1);
	}
}
