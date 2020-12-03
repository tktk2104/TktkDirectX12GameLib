#include "Act3D_PlayerCollisionReaction.h"

#include "../../../../../Enums/Enums.h"

void Act3D_PlayerCollisionReaction::onCollisionEnter(const tktk::GameObjectPtr& other)
{
	// 衝突相手が敵の攻撃範囲だったら
	if (other->containGameobjectTag(GameObjectTag::EnemyAttackRange))
	{
		// 自身に被ダメージメッセージを送る（ダメージ量は１）
		getGameObject()->sendMessage(EventMessageType::Damage, 1);
	}
}
