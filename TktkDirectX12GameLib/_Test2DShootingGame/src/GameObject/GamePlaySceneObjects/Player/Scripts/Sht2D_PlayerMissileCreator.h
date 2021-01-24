#ifndef SHT_2D_PLAYER_MISSILE_CREATOR_H_
#define SHT_2D_PLAYER_MISSILE_CREATOR_H_

#include <TktkDX12GameLib.h>
#include <TktkMath/Structs/Vector2.h>
#include "Sht2D_PlayerBulletCount.h"

class Sht2D_PlayerMissileCreator
	: public tktk::ComponentBase
{
public:

	Sht2D_PlayerMissileCreator() = default;

public:

	void start();
	void update();

private:

	std::vector<tktk::GameObjectPtr> findForwardLockOnEnemy(size_t maxFindNum) const;

	void shotMissile();

private:

	// ミサイルの速度（毎秒）
	constexpr static float				MissileSpeedPerSec			{ 2000.0f };

	// ミサイルの加速度（毎秒）
	constexpr static float				MissileAccelerationPerSec	{ 1500.0f };

	// ミサイルが前進するまでの時間（秒）
	constexpr static float				MissileActiveTimeSec		{ 0.5f };

	// ミサイルの初期移動方向（毎秒）
	constexpr static tktkMath::Vector2	InitVelocity				{ 32.0f, 0.0f };

	// ミサイルのロックオン可能角度（度数法）
	constexpr static float				MissileLockOnAngleRangeDeg	{ 45.0f };

	// ミサイルのロックオン時間
	constexpr static float				MissileLockOnTimeSec		{ 1.0f };

	// ミサイル発射間隔（秒）
	constexpr static float				ShotIntervalTimeSec			{ 1.0f };

private:

	// 発射入力時間タイマー
	float m_pushingSecTimer		{ 0.0f };

	// ロックオン完了フラグ
	bool m_lockOnReady			{ false };

	// 発射間隔タイマー
	float m_shotIntervalSecTimer{ 0.0f };

	std::array<tktk::GameObjectPtr, 2U>			m_lockOnIconObjectArray;

	tktk::ComponentPtr<tktk::Transform2D>		m_transform;

	tktk::ComponentPtr<Sht2D_PlayerBulletCount> m_playerBulletCount;
};
#endif // !SHT_2D_PLAYER_MISSILE_CREATOR_H_