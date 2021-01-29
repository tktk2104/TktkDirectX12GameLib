#include "Sht2D_EnemyCollisionReaction.h"

#include "../../../../../Enums/Enums.h"
#include "../../../Effects/Explosion/Sht2D_Explosion.h"
#include "../../../../_CommonScripts/Parameter/DamagePower/Sht2D_DamagePower.h"

void Sht2D_EnemyCollisionReaction::update()
{
	// 爆発エフェクトの出現間隔タイマーが０より大きければ
	if (m_createExplosionIntervalSecTimer > 0.0f)
	{
		// カウントダウンする
		m_createExplosionIntervalSecTimer -= tktk::DX12Game::deltaTime();
	}
}

void Sht2D_EnemyCollisionReaction::onCollisionEnter(const tktk::GameObjectPtr& other)
{
	// 衝突相手がプレイヤーの攻撃範囲だったら
	if (other->containGameobjectTag(GameObjectTag::PlayerAttackRange))
	{
		// 爆発エフェクトの出現間隔タイマーカウントが終わっていたら
		if (m_createExplosionIntervalSecTimer <= 0.0f)
		{
			tktk::ComponentPtr<tktk::Transform2D> otherTransform = other->getComponent<tktk::Transform2D>();

			// 爆発を生成する
			Sht2D_Explosion::create(
				otherTransform->getWorldPosition(),	// 生成座標
				tktkMath::Vector2_v::zero,			// 生成座標のズレ幅
				0.0f,								// 出現間隔
				1U,									// 出現数
				1.0f								// 爆発オブジェクトが消えるまでの時間（秒）
			);

			// 爆発エフェクトの出現間隔タイマーをリセット
			m_createExplosionIntervalSecTimer = CreateExplosionIntervalTimeSec;
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
		// 爆発エフェクトの出現間隔タイマーカウントが終わっていたら
		if (m_createExplosionIntervalSecTimer <= 0.0f)
		{
			// 衝突相手の座標管理コンポーネントを取得する
			tktk::ComponentPtr<tktk::Transform2D> otherTransform = other->getComponent<tktk::Transform2D>();

			// 爆発を生成する
			Sht2D_Explosion::create(
				otherTransform->getWorldPosition(),	// 生成座標
				tktkMath::Vector2_v::zero,			// 生成座標のズレ幅
				0.0f,								// 出現間隔
				1U,									// 出現数
				1.0f								// 爆発オブジェクトが消えるまでの時間（秒）
			);

			// 爆発エフェクトの出現間隔タイマーをリセット
			m_createExplosionIntervalSecTimer = CreateExplosionIntervalTimeSec;
		}

		// 自身に被ダメージメッセージを送る
		getGameObject()->sendMessage(EventMessageType::Damage, other->getComponent<Sht2D_DamagePower>()->getStayHitPowerPerSec() * tktk::DX12Game::deltaTime());
	}
}
