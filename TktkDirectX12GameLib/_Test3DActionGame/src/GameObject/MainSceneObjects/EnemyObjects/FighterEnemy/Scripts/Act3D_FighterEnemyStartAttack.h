#ifndef ACT_3D_FIGHTER_ENEMY_START_ATTACK_H_
#define ACT_3D_FIGHTER_ENEMY_START_ATTACK_H_

#include <TktkDX12GameLib.h>

// 近距離攻撃エネミーの攻撃開始処理コンポーネント
class Act3D_FighterEnemyStartAttack
	: public tktk::ComponentBase
{
public:

	Act3D_FighterEnemyStartAttack() = default;

public:

	void start();
	void update();

//************************************************************
private: /* 通常攻撃の能力 */

	// 攻撃開始できるプレイヤーとの角度差（度数法）
	static constexpr float NormalAttackStartAngleDeg	{ 45.0f };

	// 攻撃開始できるプレイヤーとの距離
	static constexpr float NormalAttackStartRange		{ 3.0f };

	// 攻撃のインターバル（秒）
	static constexpr float NormalAttackIntervalTimeSec{ 1.0f };

//************************************************************
private: /* ジャンプ攻撃の能力 */

	// 攻撃開始できるプレイヤーとの角度差（度数法）
	static constexpr float JumpAttackStartAngleDeg		{ 1.0f };

	// 攻撃開始できるプレイヤーとの距離
	static constexpr float JumpAttackStartRange			{ 7.0f };

	// 攻撃のインターバル（秒）
	static constexpr float JumpAttackIntervalTimeSec	{ 1.5f };

private:

	// 攻撃間隔を管理するタイマー
	float									m_attackIntervelSecTimer{ 0.0f };

	// 自身の座標管理コンポーネント
	tktk::ComponentPtr<tktk::Transform3D>	m_selfTransform;

	// プレイヤーの座標管理コンポーネント
	tktk::ComponentPtr<tktk::Transform3D>	m_playerTransform;
};
#endif // !ACT_3D_FIGHTER_ENEMY_START_ATTACK_H_
