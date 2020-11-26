#include "Act3D_GameRuleScripts.h"

#include "../../../Enums/Enums.h"

#include "../../EnemyObjects/FighterEnemy/Act3D_FighterEnemy.h"
#include "../../EnemyObjects/ShooterEnemy/Act3D_ShooterEnemy.h"
#include "../../EnemyObjects/BossEnemy/Act3D_BossEnemy.h"

#include "../../MainSceneObjects/MainSceneChanger/Act3D_MainSceneChanger.h"

void Act3D_GameRuleScripts::start()
{
	m_playerObject = tktk::DX12Game::findGameObjectWithTag(GameObjectTag::Player);
}

void Act3D_GameRuleScripts::update()
{
	if (!m_gamePlaying) return;

	if (m_playerObject.expired() || m_playerObject->containState(PlayerStateType::Dead))
	{
		// シーン遷移コンポーネントを作る
		Act3D_MainSceneChanger::create();

		m_isGameOver = true;

		m_gamePlaying = false;

		return;
	}

	if (m_sendPlayerMessageNextFrame)
	{
		m_playerObject->sendMessage(EventMessageType::LookToEnemy);
		m_sendPlayerMessageNextFrame = false;
	}

	spawnEnemyCheck();
}

bool Act3D_GameRuleScripts::isGameOver() const
{
	return m_isGameOver;
}

void Act3D_GameRuleScripts::spawnEnemyCheck()
{
	auto enemyObjectList = tktk::DX12Game::findGameObjectsWithTag(GameObjectTag::Enemy);

	// 敵が存在しなかったら
	if (enemyObjectList.empty())
	{
		if (m_enemySpawnCounter >= static_cast<int>(SpawnData.size()))
		{
			// シーン遷移コンポーネントを作る
			Act3D_MainSceneChanger::create();

			m_gamePlaying = false;

			return;
		}

		auto rotateDir = m_playerObject->getComponent<tktk::Transform3D>()->getWorldPosition() - tktkMath::Vector3_v::zero;

		switch (SpawnData.at(m_enemySpawnCounter))
		{
		case SpawnEnemyType::Fighter:

			Act3D_FighterEnemy::create(tktkMath::Vector3_v::zero, { 0.0f, tktkMath::Vector2::signedAngle({ rotateDir.x, rotateDir.z }, tktkMath::Vector2_v::up), 0.0f });
			break;

		case SpawnEnemyType::Shooter:

			Act3D_ShooterEnemy::create(tktkMath::Vector3_v::zero, { 0.0f, tktkMath::Vector2::signedAngle({ rotateDir.x, rotateDir.z }, tktkMath::Vector2_v::up), 0.0f });
			break;

		case SpawnEnemyType::Boss:

			Act3D_BossEnemy::create(tktkMath::Vector3_v::zero, { 0.0f, tktkMath::Vector2::signedAngle({ rotateDir.x, rotateDir.z }, tktkMath::Vector2_v::up), 0.0f });
			break;
		}

		++m_enemySpawnCounter;
		m_sendPlayerMessageNextFrame = true;
	}
}
