#ifndef SHT_2D_SPREAD_BULLET_ENEMY_BULLET_CREATOR_H_
#define SHT_2D_SPREAD_BULLET_ENEMY_BULLET_CREATOR_H_

#include <TktkDX12GameLib.h>

// 拡散弾エネミーの弾生成コンポーネント
class Sht2D_SpreadBulletEnemyBulletCreator
	: public tktk::ComponentBase
{
public:

	Sht2D_SpreadBulletEnemyBulletCreator() = default;

public:

	void start();
	void update();

private:

	// 毎秒の弾の移動速度
	constexpr static float	BulletSpeedPerSec			{ 512.0f };

	// 一度に何発の弾を生成するか？
	constexpr static size_t CreateBulletCountPerOnce	{ 3U };

	// 弾の発射間隔タイマー（秒）
	constexpr static float	ShotIntervalTimeSec			{ 0.1f };

	// 発射ごとの弾の発射角の差（度数法）
	constexpr static float	ShotBulletAngleDistDeg		{ 66.0f };

private:

	// 現在の弾の発射角の基準値（度数法）
	float m_curBaseShotAngleDeg		{ 0.0f };

	// 弾の発射間隔タイマー（秒）
	float m_shotIntervalSecTimer	{ 0.0f };

	tktk::ComponentPtr<tktk::Transform2D> m_transform;

	tktk::ComponentPtr<tktk::InertialMovement2D> m_inertialMovement;
};
#endif // !SHT_2D_SPREAD_BULLET_ENEMY_BULLET_CREATOR_H_