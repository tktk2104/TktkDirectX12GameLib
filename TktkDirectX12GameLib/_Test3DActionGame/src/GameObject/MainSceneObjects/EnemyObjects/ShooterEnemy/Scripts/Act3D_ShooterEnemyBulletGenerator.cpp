#include "Act3D_ShooterEnemyBulletGenerator.h"

#include <stdexcept>
#include "../../../../../Enums/Enums.h"
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
	m_generateSecTimer = GenerateTimeSec;
}

void Act3D_ShooterEnemyBulletGenerator::update()
{
	// 既に弾を発射していたら処理を終える
	if (m_endShot) return;

	// プレイヤーの座標管理コンポーネントが取得できていなければ
	if (m_playerTransform.expired())
	{
		// プレイヤーオブジェクトを取得する
		auto player = tktk::DX12Game::findGameObjectWithTag(GameObjectTag::Player);

		// プレイヤーオブジェクトが取得できなければ処理を終える
		if (player.expired()) return;

		// プレイヤーの座標管理コンポーネントを取得する
		m_playerTransform = player->getComponent<tktk::Transform3D>();

		// プレイヤーが座標管理コンポーネントを持っていなければ処理を終える
		if (m_playerTransform.expired()) return;
	}

	// タイマーのカウントがゼロになっていたら
	if (m_generateSecTimer < 0.0f)
	{
		const auto& selfPos		= m_selfTransform->getWorldPosition();
		const auto& playerPos	= m_playerTransform->getWorldPosition();

		// 発射する弾の発射方向
		auto bulletDirection = (playerPos - selfPos).normalized();

		// 遠距離攻撃エネミーの弾を生成する
		Act3D_ShooterEnemyBullet::create(selfPos + GeneratePos, bulletDirection * BulletSpeed);

		// 弾の発射フラグを立てる
		m_endShot = true;
	}

	// タイマーをカウントダウンする
	m_generateSecTimer -= tktk::DX12Game::deltaTime();
}
