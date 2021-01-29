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
	// 弾の発射間隔タイマーカウントが０以上だったら
	if (m_shotIntervalSecTimer > 0.0f)
	{
		// 発射間隔タイマーをカウントダウンしてこの関数を終える
		m_shotIntervalSecTimer -= tktk::DX12Game::deltaTime();
		return;
	}

	// １度に発射する弾の数分だけループする
	for (size_t i = 0; i < CreateBulletCountPerOnce; i++)
	{
		// 発射角度を計算する
		float shotAngle = m_curBaseShotAngleDeg + (360.0f / CreateBulletCountPerOnce * i);

		// 敵の通常弾を生成する
		Sht2D_EnemyNormalBullet::create(
			m_transform->getWorldPosition(),
			shotAngle,
			tktkMath::Matrix3::createRotation(shotAngle).calculateUp() * BulletSpeedPerSec + m_inertialMovement->getVelocity()
		);
	}

	// 弾の発射角度の基準値を更新する
	m_curBaseShotAngleDeg += ShotBulletAngleDistDeg;

	// 360度超えた時の補正値
	if (m_curBaseShotAngleDeg >= 360.0f) m_curBaseShotAngleDeg -= 360.0f;

	// 弾の発射間隔タイマーをリセットする
	m_shotIntervalSecTimer = ShotIntervalTimeSec;
}