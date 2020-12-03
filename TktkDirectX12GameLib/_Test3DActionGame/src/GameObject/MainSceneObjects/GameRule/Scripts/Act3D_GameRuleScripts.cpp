#include "Act3D_GameRuleScripts.h"

#include "../../../../Enums/Enums.h"

#include "../../EnemyObjects/FighterEnemy/Act3D_FighterEnemy.h"
#include "../../EnemyObjects/ShooterEnemy/Act3D_ShooterEnemy.h"
#include "../../EnemyObjects/BossEnemy/Act3D_BossEnemy.h"

#include "../../../MainSceneObjects/MainSceneChanger/Act3D_MainSceneChanger.h"

void Act3D_GameRuleScripts::start()
{
	m_playerObject = tktk::DX12Game::findGameObjectWithTag(GameObjectTag::Player);
}

void Act3D_GameRuleScripts::update()
{
	// ゲームが終了していたら処理を終える
	if (!m_gamePlaying) return;

	// プレイヤーが死亡していたら
	if (m_playerObject.expired() || m_playerObject->containState(PlayerStateType::Dead))
	{
		// シーン遷移コンポーネントを作る
		Act3D_MainSceneChanger::create();

		// ゲームオーバーフラグを立てる
		m_isGameOver = true;

		// ゲームプレイ中フラグを折る
		m_gamePlaying = false;

		return;
	}

	// プレイヤーへメッセージを送信するフラグが立っていたた
	if (m_sendPlayerMessageNextFrame)
	{
		// プレイヤーに敵の方へ向くメッセージを送信する
		m_playerObject->sendMessage(EventMessageType::LookToEnemy);

		// メッセージ送信フラグを折る
		m_sendPlayerMessageNextFrame = false;
	}

	// 敵の出現処理を行う
	spawnEnemyCheck();
}

bool Act3D_GameRuleScripts::isGameOver() const
{
	return m_isGameOver;
}

void Act3D_GameRuleScripts::spawnEnemyCheck()
{
	// 敵オブジェクトのリストを取得する
	auto enemyObjectList = tktk::DX12Game::findGameObjectsWithTag(GameObjectTag::Enemy);

	// 敵が存在しなかったら
	if (enemyObjectList.empty())
	{
		// 全ての敵が出現していたら
		if (m_enemySpawnCounter >= static_cast<int>(SpawnData.size()))
		{
			// シーン遷移コンポーネントを作る
			Act3D_MainSceneChanger::create();

			// ゲームプレイ中フラグを折る
			m_gamePlaying = false;

			return;
		}

		// 生成するエネミーの向いてる方向を表すベクトルを計算する
		auto rotateDir = m_playerObject->getComponent<tktk::Transform3D>()->getWorldPosition() - tktkMath::Vector3_v::zero;

		// 出現させる敵の種類で分岐
		switch (SpawnData.at(m_enemySpawnCounter))
		{
		// 近距離攻撃エネミーの場合
		case SpawnEnemyType::Fighter:

			// 近距離攻撃エネミーを生成する
			Act3D_FighterEnemy::create(tktkMath::Vector3_v::zero, { 0.0f, tktkMath::Vector2::signedAngle({ rotateDir.x, rotateDir.z }, tktkMath::Vector2_v::up), 0.0f });
			break;

		// 遠距離攻撃エネミーの場合
		case SpawnEnemyType::Shooter:

			// 遠距離攻撃エネミーを生成する
			Act3D_ShooterEnemy::create(tktkMath::Vector3_v::zero, { 0.0f, tktkMath::Vector2::signedAngle({ rotateDir.x, rotateDir.z }, tktkMath::Vector2_v::up), 0.0f });
			break;

		// ボスエネミーの場合
		case SpawnEnemyType::Boss:

			// ボスエネミーを生成する
			Act3D_BossEnemy::create(tktkMath::Vector3_v::zero, { 0.0f, tktkMath::Vector2::signedAngle({ rotateDir.x, rotateDir.z }, tktkMath::Vector2_v::up), 0.0f });
			break;
		}

		// 敵の出現数カウンタをインクリメントする
		++m_enemySpawnCounter;

		// 次のフレームでプレイヤーにメッセージを送信するフラグを立てる
		m_sendPlayerMessageNextFrame = true;
	}
}
