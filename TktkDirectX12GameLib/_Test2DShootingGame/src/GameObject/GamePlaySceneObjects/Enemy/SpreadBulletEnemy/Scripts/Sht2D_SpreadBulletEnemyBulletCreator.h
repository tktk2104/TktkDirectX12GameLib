#ifndef SHT_2D_SPREAD_BULLET_ENEMY_BULLET_CREATOR_H_
#define SHT_2D_SPREAD_BULLET_ENEMY_BULLET_CREATOR_H_

#include <TktkDX12GameLib.h>

class Sht2D_SpreadBulletEnemyBulletCreator
	: public tktk::ComponentBase
{
public:

	Sht2D_SpreadBulletEnemyBulletCreator() = default;

public:

	void start();
	void update();

private:

	constexpr static float	BulletSpeedPerSec			{ 512.0f };

	constexpr static size_t CreateBulletCountPerOnce	{ 3U };

	constexpr static float	ShotIntervalTimeSec			{ 0.1f };

	constexpr static float	ShotBulletAngleDist			{ 22.0f };

private:

	float m_curBaseShotAngle		{ 0.0f };

	float m_shotIntervalSecTimer{ 0.0f };

	tktk::ComponentPtr<tktk::Transform2D> m_transform;

	tktk::ComponentPtr<tktk::InertialMovement2D> m_inertialMovement;
};
#endif // !SHT_2D_SPREAD_BULLET_ENEMY_BULLET_CREATOR_H_