#include "Sht2D_PlayerNormalBulletCollisionReaction.h"

#include "../../../../../Enums/Enums.h"

void Sht2D_PlayerNormalBulletCollisionReaction::onCollisionEnter(const tktk::GameObjectPtr& other)
{
	// 衝突相手が敵だったら
	if (other->containGameobjectTag(GameObjectTag::Enemy))
	{
		// 自身の所持者を殺す
		getGameObject()->destroy();
	}
}