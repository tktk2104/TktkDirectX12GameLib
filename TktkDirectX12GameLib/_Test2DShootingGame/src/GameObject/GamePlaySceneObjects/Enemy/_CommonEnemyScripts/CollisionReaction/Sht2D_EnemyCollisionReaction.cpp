#include "Sht2D_EnemyCollisionReaction.h"

#include "../../../../../Enums/Enums.h"
#include "../../../Effects/Explosion/Sht2D_Explosion.h"
#include "../../../../_CommonScripts/Parameter/DamagePower/Sht2D_DamagePower.h"

void Sht2D_EnemyCollisionReaction::update()
{
	if (m_createExplosionIntervalSecTimer < CreateExplosionIntervalTimeSec)
	{
		m_createExplosionIntervalSecTimer += tktk::DX12Game::deltaTime();
	}
}

void Sht2D_EnemyCollisionReaction::onCollisionEnter(const tktk::GameObjectPtr& other)
{
	// 衝突相手がプレイヤーの攻撃範囲だったら
	if (other->containGameobjectTag(GameObjectTag::PlayerAttackRange))
	{
		auto otherTransform = other->getComponent<tktk::Transform2D>();

		if (m_createExplosionIntervalSecTimer >= CreateExplosionIntervalTimeSec)
		{
			// 爆発を生成する
			Sht2D_Explosion::create(
				otherTransform->getWorldPosition(),
				tktkMath::Vector2_v::zero,
				0.0f,
				1U,
				1.0f
			);

			m_createExplosionIntervalSecTimer = 0.0f;
		}

		// 自身に被ダメージメッセージを送る
		getGameObject()->sendMessage(EventMessageType::Damage, other->getComponent<Sht2D_DamagePower>()->getStartHitPower());
	}
}

void Sht2D_EnemyCollisionReaction::onCollisionStay(const tktk::GameObjectPtr& other)
{
	// 衝突相手がプレイヤーの攻撃範囲だったら
	if (other->containGameobjectTag(GameObjectTag::PlayerAttackRange))
	{
		auto otherTransform = other->getComponent<tktk::Transform2D>();

		if (m_createExplosionIntervalSecTimer >= CreateExplosionIntervalTimeSec)
		{
			// 爆発を生成する
			Sht2D_Explosion::create(
				otherTransform->getWorldPosition(),
				tktkMath::Vector2_v::zero,
				0.0f,
				1U,
				1.0f
			);

			m_createExplosionIntervalSecTimer = 0.0f;
		}

		// 自身に被ダメージメッセージを送る
		getGameObject()->sendMessage(EventMessageType::Damage, other->getComponent<Sht2D_DamagePower>()->getStayHitPowerPerSec() * tktk::DX12Game::deltaTime());
	}
}
