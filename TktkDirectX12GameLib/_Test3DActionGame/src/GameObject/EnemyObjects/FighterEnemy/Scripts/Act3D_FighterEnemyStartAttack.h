#ifndef ACT_3D_FIGHTER_ENEMY_START_ATTACK_H_
#define ACT_3D_FIGHTER_ENEMY_START_ATTACK_H_

#include <TktkDX12GameLib.h>

class Act3D_FighterEnemyStartAttack
	: public tktk::ComponentBase
{
public:

	Act3D_FighterEnemyStartAttack() = default;

public:

	void start();
	void update();

private:

	// 通常攻撃を開始する“真上から見た「エネミーの正面ベクトルと、プレイヤー方向のベクトル」の間の角”の最大値（度数法）
	static constexpr float NormalAttackStartAngleDeg	{ 45.0f };

	// ジャンプ攻撃を開始する“真上から見た「エネミーの正面ベクトルと、プレイヤー方向のベクトル」の間の角”の最大値（度数法）
	static constexpr float JumpAttackStartAngleDeg		{ 1.0f };

	// 通常攻撃を開始するプレイヤーとの距離
	static constexpr float NormalAttackStartRange		{ 3.0f };

	// ジャンプ攻撃を開始するプレイヤーとの距離
	static constexpr float JumpAttackStartRange			{ 7.0f };

	// 通常攻撃から始まった攻撃が終わった後、再び攻撃できるようになるまでの時間（秒）
	static constexpr float NormalAttackIntervalTimeSec	{ 1.0f };

	// ジャンプ攻撃から始まった攻撃が終わった後、再び攻撃できるようになるまでの時間（秒）
	static constexpr float JumpAttackIntervalTimeSec	{ 1.5f };

private:

	float									m_attackIntervelSecTimer{ 0.0f };
	tktk::ComponentPtr<tktk::Transform3D>	m_selfTransform;
	tktk::ComponentPtr<tktk::Transform3D>	m_playerTransform;
};
#endif // !ACT_3D_FIGHTER_ENEMY_START_ATTACK_H_
