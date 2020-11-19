#include "Act3D_ShooterEnemyBulletGenerator.h"

#include <stdexcept>
#include "../../../../Enums/Enums.h"
#include "../../EnemyBullet/ShooterEnemyBullet/Act3D_ShooterEnemyBullet.h"

void Act3D_ShooterEnemyBulletGenerator::start()
{
	m_selfTransform = getComponent<tktk::Transform3D>();

	if (m_selfTransform.expired())
	{
		throw std::runtime_error("Act3D_FindPlayer not found Transform3D");
	}
}

void Act3D_ShooterEnemyBulletGenerator::onEnable()
{
	// 発射フラグを折る
	m_endShot = false;

	// タイマーを初期化する
	m_agenerateSecTimer = GenerateTimeSec;
}

void Act3D_ShooterEnemyBulletGenerator::update()
{
	if (m_endShot) return;

	if (m_playerTransform.expired())
	{
		auto player = tktk::DX12Game::findGameObjectWithTag(GameObjectTag::Player);

		if (player.expired()) return;

		m_playerTransform = player->getComponent<tktk::Transform3D>();

		if (m_playerTransform.expired()) return;
	}

	if (m_agenerateSecTimer < 0.0f)
	{
		const auto& selfPos		= m_selfTransform->getWorldPosition();
		const auto& playerPos	= m_playerTransform->getWorldPosition();

		auto bulletDirection = (playerPos - selfPos).normalized();

		Act3D_ShooterEnemyBullet::create(selfPos + GeneratePos, bulletDirection * BulletSpeed);

		m_endShot = true;
	}

	// タイマーを更新する
	m_agenerateSecTimer -= tktk::DX12Game::deltaTime();
}
