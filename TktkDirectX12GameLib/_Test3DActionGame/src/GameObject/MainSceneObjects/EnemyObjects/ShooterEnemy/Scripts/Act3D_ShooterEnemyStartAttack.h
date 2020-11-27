#ifndef ACT_3D_SHOOTER_ENEMY_START_ATTACK_H_
#define ACT_3D_SHOOTER_ENEMY_START_ATTACK_H_

#include <TktkDX12GameLib.h>

// 遠距離攻撃エネミーの攻撃開始処理コンポーネント
class Act3D_ShooterEnemyStartAttack
	: public tktk::ComponentBase
{
public:

	Act3D_ShooterEnemyStartAttack() = default;

public:

	void start();
	void update();

//************************************************************
private: /* 近距離攻撃の能力 */

	// 攻撃開始できるプレイヤーとの角度差（度数法）
	static constexpr float ShortRangeAttackStartAngleDeg	{ 45.0f };

	// 攻撃開始できるプレイヤーとの距離
	static constexpr float ShortRangeAttackStartRange		{ 3.0f };

	// 攻撃のインターバル（秒）
	static constexpr float ShortRangeAttackIntervalTimeSec	{ 1.0f };

//************************************************************
private: /* 遠距離攻撃の能力 */

	// 攻撃開始できるプレイヤーとの角度差（度数法）
	static constexpr float LongRangeAttackStartAngleDeg		{ 1.0f };

	// 攻撃開始できるプレイヤーとの距離
	static constexpr float LongRangeAttackStartRange		{ 30.0f };

	// 攻撃のインターバル（秒）
	static constexpr float LongRangeAttackIntervalTimeSec	{ 2.0f };

private:

	// 攻撃間隔を管理するタイマー
	float									m_attackIntervelSecTimer{ 0.0f };

	// 自身の座標管理コンポーネント
	tktk::ComponentPtr<tktk::Transform3D>	m_selfTransform;

	// プレイヤーの座標管理コンポーネント
	tktk::ComponentPtr<tktk::Transform3D>	m_playerTransform;
};
#endif // !ACT_3D_SHOOTER_ENEMY_START_ATTACK_H_