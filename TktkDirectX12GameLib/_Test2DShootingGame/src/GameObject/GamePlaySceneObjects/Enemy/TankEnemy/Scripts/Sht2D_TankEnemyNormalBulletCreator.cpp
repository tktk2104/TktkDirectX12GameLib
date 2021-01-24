#include "Sht2D_TankEnemyNormalBulletCreator.h"

#include "../../../../../Enums/Enums.h"
#include "../../../EnemyBullets/EnemyNormalBullet/Sht2D_EnemyNormalBullet.h"

void Sht2D_TankEnemyNormalBulletCreator::start()
{
	m_transform = getComponent<tktk::Transform2D>();

	if (m_transform.expired())
	{
		throw std::runtime_error("Sht2D_TankEnemyNormalBulletCreator not found Transform2D");
	}
}

void Sht2D_TankEnemyNormalBulletCreator::update()
{
	if (m_shotIntervalSecTimer > 0.0f)
	{
		m_shotIntervalSecTimer -= tktk::DX12Game::deltaTime();
		return;
	}

	Sht2D_EnemyNormalBullet::create(tktkMath::Vector2(0.0f, -64.0f) * m_transform->calculateWorldMatrix(), m_transform->getWorldRotationDeg(), m_transform->calculateWorldUp() * BulletSpeedPerSec);

	m_shotIntervalSecTimer = ShotIntervalTimeSec;
}
