#include "Sht2D_SpreadBulletEnemyBulletCreator.h"

#include "../../../../../Enums/Enums.h"
#include "../../../EnemyBullets/EnemyNormalBullet/Sht2D_EnemyNormalBullet.h"

void Sht2D_SpreadBulletEnemyBulletCreator::start()
{
	m_transform = getComponent<tktk::Transform2D>();

	if (m_transform.expired())
	{
		throw std::runtime_error("Sht2D_SpreadBulletEnemyBulletCreator not found Transform2D");
	}

	m_inertialMovement = getComponent<tktk::InertialMovement2D>();

	if (m_inertialMovement.expired())
	{
		throw std::runtime_error("Sht2D_SpreadBulletEnemyBulletCreator not found InertialMovement2D");
	}
}

void Sht2D_SpreadBulletEnemyBulletCreator::update()
{
	if (m_shotIntervalSecTimer > 0.0f)
	{
		m_shotIntervalSecTimer -= tktk::DX12Game::deltaTime();
		return;
	}

	for (size_t i = 0; i < CreateBulletCountPerOnce; i++)
	{
		float shotAngle = m_curBaseShotAngle + (360.0f / CreateBulletCountPerOnce * i);

		Sht2D_EnemyNormalBullet::create(
			m_transform->getWorldPosition(),
			shotAngle,
			tktkMath::Matrix3::createRotation(shotAngle).calculateUp() * BulletSpeedPerSec + m_inertialMovement->getVelocity()
		);

		m_curBaseShotAngle += ShotBulletAngleDist;

		if (m_curBaseShotAngle >= 360.0f) m_curBaseShotAngle -= 360.0f;
	}

	m_shotIntervalSecTimer = ShotIntervalTimeSec;
}