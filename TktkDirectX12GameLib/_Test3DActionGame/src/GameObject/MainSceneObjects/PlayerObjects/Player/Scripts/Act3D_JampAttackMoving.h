#ifndef ACT_3D_JAMP_ATTACK_MOVING_H_
#define ACT_3D_JAMP_ATTACK_MOVING_H_

#include <TktkDX12GameLib.h>

// ジャンプ攻撃の移動を行うコンポーネント
class Act3D_JampAttackMoving
	: public tktk::ComponentBase
{
public:

	Act3D_JampAttackMoving() = default;

public:

	void start();
	void onEnable();
	void update();

private:

	// 垂直方向にかける瞬間的な力
	constexpr static float JumpVerticalPower			{ 4.5f };

	// 垂直方向に何秒後移動するか？
	constexpr static float JmupVerticalMoveStartTimeSec	{ 0.1f };

	// 水平方向にかける継続的な力（毎秒）
	constexpr static float JumpHorizontalSpeedPerSec	{ 5.0f };

	// 水平方向に何秒間移動するか？
	constexpr static float JmupHorizontalMoveTimeSec	{ 1.3f };

private:

	// 垂直移動を開始する時間を表すタイマー
	float											m_verticalMoveSecTimer		{ 0.0f };

	// 垂直移動を行ったかどうかのフラグ
	bool											m_afterVerticalMove			{ false };

	// 水平移動を行う時間を表すタイマー
	float											m_horizontalMoveSecTimer	{ 0.0f };

	// 座標管理コンポーネント
	tktk::ComponentPtr<tktk::Transform3D>			m_transform;

	// 慣性移動コンポーネント
	tktk::ComponentPtr<tktk::InertialMovement3D>	m_inertialMovement;
};
#endif // !ACT_3D_JAMP_ATTACK_MOVING_H_