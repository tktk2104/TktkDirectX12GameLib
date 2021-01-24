#include "Sht2D_PlayerCollisionReaction.h"

#include "../../../../Enums/Enums.h"
#include "../../Effects/Explosion/Sht2D_Explosion.h"
#include "../../../_CommonScripts/Parameter/DamagePower/Sht2D_DamagePower.h"

void Sht2D_PlayerCollisionReaction::update()
{
	if (m_createExplosionIntervalSecTimer < CreateExplosionIntervalTimeSec)
	{
		m_createExplosionIntervalSecTimer += tktk::DX12Game::deltaTime();
	}
}

void Sht2D_PlayerCollisionReaction::onCollisionEnter(const tktk::GameObjectPtr& other)
{
	// 衝突相手が敵の攻撃範囲だったら
	if (other->containGameobjectTag(GameObjectTag::EnemyAttackRange))
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

void Sht2D_PlayerCollisionReaction::onCollisionStay(const tktk::GameObjectPtr& other)
{
	// 衝突相手が敵の攻撃範囲だったら
	if (other->containGameobjectTag(GameObjectTag::EnemyAttackRange))
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
