#include "Act3D_EnemyCollisionReaction.h"

#include "../../../../Enums/Enums.h"

void Act3D_EnemyCollisionReaction::onCollisionEnter(const tktk::GameObjectPtr& other)
{
	// 衝突相手がプレイヤーの攻撃判定だったら
	if (other->containGameobjectTag(GameObjectTag::PlayerAttackRange))
	{
		// 自身に被ダメージメッセージを送る（ダメージは１）
  		getGameObject()->sendMessage(EventMessageType::Damage, 1);
	}
}
