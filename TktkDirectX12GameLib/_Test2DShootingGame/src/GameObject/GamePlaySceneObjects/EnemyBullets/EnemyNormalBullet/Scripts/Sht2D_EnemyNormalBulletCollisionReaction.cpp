#include "Sht2D_EnemyNormalBulletCollisionReaction.h"

#include "../../../../../Enums/Enums.h"

void Sht2D_EnemyNormalBulletCollisionReaction::onCollisionEnter(const tktk::GameObjectPtr& other)
{
	// 衝突相手がプレイヤーだったら
	if (other->containGameobjectTag(GameObjectTag::Player))
	{
		// 自身の所持者を殺す
		getGameObject()->destroy();
	}
}