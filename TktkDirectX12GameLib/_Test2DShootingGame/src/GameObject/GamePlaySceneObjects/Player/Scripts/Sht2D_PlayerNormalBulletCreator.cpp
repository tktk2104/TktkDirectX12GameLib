#include "Sht2D_PlayerNormalBulletCreator.h"

#include "../../../../Enums/Enums.h"
#include "../../PlayerBullets/PlayerNormalBullet/Sht2D_PlayerNormalBullet.h"

void Sht2D_PlayerNormalBulletCreator::start()
{
	m_transform = getComponent<tktk::Transform2D>();

	if (m_transform.expired())
	{
		throw std::runtime_error("Sht2D_PlayerNormalBulletCreator not found Transform2D");
	}
}

void Sht2D_PlayerNormalBulletCreator::update()
{
	// 弾の発射間隔タイマーカウンタが０以上だったら
	if (m_shotIntervalSecTimer > 0.0f)
	{
		// カウントダウンして関数を終える
		m_shotIntervalSecTimer -= tktk::DX12Game::deltaTime();
		return;
	}

	// 弾発射入力が押されていたら
	if (tktk::DX12Game::isPush(CommandId::ShotBullet))
	{
		// プレイヤー通常弾を作る（生成座標、生成時回転、弾発射速度）
		Sht2D_PlayerNormalBullet::create(tktkMath::Vector2(0.0f, -64.0f) * m_transform->calculateWorldMatrix(), m_transform->getWorldRotationDeg(), BulletSpeedPerSec);

		// 弾の発射間隔タイマーを初期化する
		m_shotIntervalSecTimer = ShotIntervalTimeSec;
	}
}
