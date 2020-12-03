#ifndef ACT_3D_ENEMY_JAMP_ATTACK_MOVING_H_
#define ACT_3D_ENEMY_JAMP_ATTACK_MOVING_H_

#include <TktkDX12GameLib.h>

// ジャンプ攻撃の移動処理を行うコンポーネント
class Act3D_EnemyJampAttackMoving
	: public tktk::ComponentBase
{
public:

	Act3D_EnemyJampAttackMoving(
		float jumpVerticalPower,
		float jmupVerticalMoveStartTimeSec,
		float jumpHorizontalSpeedPerSec,
		float jmupHorizontalMoveTimeSec
	);

public:

	void start();
	void onEnable();
	void update();

private:

	// 垂直方向にかける瞬間的な力
	float											m_jumpVerticalPower;

	// 垂直方向に何秒後移動するか？
	float											m_jmupVerticalMoveStartTimeSec;

	// 水平方向にかける継続的な力（毎秒）
	float											m_jumpHorizontalSpeedPerSec;

	// 水平方向に何秒間移動するか？
	float											m_jmupHorizontalMoveTimeSec;

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
#endif // !ACT_3D_ENEMY_JAMP_ATTACK_MOVING_H_