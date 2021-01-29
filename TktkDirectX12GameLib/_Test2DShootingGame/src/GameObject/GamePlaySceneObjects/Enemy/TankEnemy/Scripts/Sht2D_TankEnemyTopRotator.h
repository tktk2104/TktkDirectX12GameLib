#ifndef SHT_2D_TANK_ENEMY_TOP_ROTATOR_H_
#define SHT_2D_TANK_ENEMY_TOP_ROTATOR_H_

#include <TktkDX12GameLib.h>

// 戦車の砲塔の回転コンポーネント
class Sht2D_TankEnemyTopRotator
	: public tktk::ComponentBase
{
public:

	Sht2D_TankEnemyTopRotator() = default;

public:

	void start();
	void update();

private:

	// 回転先座標のオフセット値（なんちゃって偏差射撃）
	constexpr static tktkMath::Vector2 TargetOffset	{ 0.0f, -64.0f };

	// 毎秒の最大回転幅（度数法）
	constexpr static float RotateSpeedPerSecDeg		{ 30.0f };

private:

	tktk::ComponentPtr<tktk::Transform2D> m_transform;
};
#endif // !SHT_2D_TANK_ENEMY_TOP_ROTATOR_H_
