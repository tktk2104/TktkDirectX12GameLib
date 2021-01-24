#include "Sht2D_PlayerNormalBulletCollisionReaction.h"

#include "../../../../../Enums/Enums.h"

void Sht2D_PlayerNormalBulletCollisionReaction::onCollisionEnter(const tktk::GameObjectPtr& other)
{
	// Õ“Ë‘ŠŽè‚ª“G‚¾‚Á‚½‚ç
	if (other->containGameobjectTag(GameObjectTag::Enemy))
	{
		// Ž©g‚ÌŠŽŽÒ‚ðŽE‚·
		getGameObject()->destroy();
	}
}