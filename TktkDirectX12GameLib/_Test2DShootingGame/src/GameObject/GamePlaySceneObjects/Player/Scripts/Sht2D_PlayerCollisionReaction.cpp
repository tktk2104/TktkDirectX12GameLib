#include "Sht2D_PlayerCollisionReaction.h"

#include "../../../../Enums/Enums.h"
#include "../../Effects/Explosion/Sht2D_Explosion.h"
#include "../../../_CommonScripts/Parameter/DamagePower/Sht2D_DamagePower.h"

void Sht2D_PlayerCollisionReaction::update()
{
	// 爆発エフェクトの出現間隔タイマーが０より大きければ
	if (m_createExplosionIntervalSecTimer > 0.0f)
	{
		// カウントダウンする
		m_createExplosionIntervalSecTimer -= tktk::DX12Game::deltaTime();
	}
}

void Sht2D_PlayerCollisionReaction::onCollisionEnter(const tktk::GameObjectPtr& other)
{
  /*┌────────────────────────────────────────────────────────────────────────────────────────
    │指定のゲームオブジェクトが特定のタグを持っているか判別したい時は「gameObject->containGameobjectTag(tag)」を使って下さい。
    └────────────────────────────────────────────────────────────────────────────────────────*/

	// 衝突相手が敵の攻撃範囲だったら
	if (other->containGameobjectTag(GameObjectTag::EnemyAttackRange))
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
				1,									// 出現数
				1.0f								// 爆発オブジェクトが消えるまでの時間（秒）
			);

			// 爆発エフェクトの出現間隔タイマーをリセット
			m_createExplosionIntervalSecTimer = CreateExplosionIntervalTimeSec;
		}


	  /*┌────────────────────────────────────────────────────────────────────────────────────────
	    │「gameObject->sendMessage(messageType, anyValue)」で特定のオブジェクトにメッセージを送信する事ができます。
		│　メッセージは送られたオブジェクトの全コンポーネント、全子要素に伝達され、「handleMessage(messageType, anyValue)」で検知が行えます。
		│　第二引数にはあらゆる型の値を持たせることができます。（今回はfloat型を渡しています。）
		│　※「EventMessageType」は自分で作る列挙型です。
	    └────────────────────────────────────────────────────────────────────────────────────────*/

		// 自身に被ダメージメッセージを送る
		getGameObject()->sendMessage(EventMessageType::Damage, other->getComponent<Sht2D_DamagePower>()->getStartHitPower());
	}
}

void Sht2D_PlayerCollisionReaction::onCollisionStay(const tktk::GameObjectPtr& other)
{
	// 衝突相手が敵の攻撃範囲だったら
	if (other->containGameobjectTag(GameObjectTag::EnemyAttackRange))
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
				1,									// 出現数
				1.0f								// 爆発オブジェクトが消えるまでの時間（秒）
			);

			// 爆発エフェクトの出現間隔タイマーをリセット
			m_createExplosionIntervalSecTimer = CreateExplosionIntervalTimeSec;
		}

		// 自身に被ダメージメッセージを送る
		getGameObject()->sendMessage(EventMessageType::Damage, other->getComponent<Sht2D_DamagePower>()->getStayHitPowerPerSec() * tktk::DX12Game::deltaTime());
	}
}
