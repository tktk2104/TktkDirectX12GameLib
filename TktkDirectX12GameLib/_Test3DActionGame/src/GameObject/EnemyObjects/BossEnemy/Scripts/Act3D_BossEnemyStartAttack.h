#ifndef ACT_3D_BOSS_ENEMY_START_ATTACK_H_
#define ACT_3D_BOSS_ENEMY_START_ATTACK_H_

#include <TktkDX12GameLib.h>

class Act3D_BossEnemyStartAttack
	: public tktk::ComponentBase
{
public:

	Act3D_BossEnemyStartAttack() = default;

public:

	void start();
	void update();

private:

	// 通常攻撃を開始する“真上から見た「エネミーの正面ベクトルと、プレイヤー方向のベクトル」の間の角”の最大値（度数法）
	static constexpr float NormalAttackStartAngleDeg{ 45.0f };

	// ローリング攻撃を開始する“真上から見た「エネミーの正面ベクトルと、プレイヤー方向のベクトル」の間の角”の最大値（度数法）
	static constexpr float RollAttackStartAngleDeg{ 45.0f };

	// ジャンプ攻撃を開始する“真上から見た「エネミーの正面ベクトルと、プレイヤー方向のベクトル」の間の角”の最大値（度数法）
	static constexpr float JumpAttackStartAngleDeg{ 1.0f };

	// 通常攻撃を開始するプレイヤーとの距離
	static constexpr float NormalAttackStartRange{ 4.0f };

	// ローリング攻撃を開始するプレイヤーとの距離
	static constexpr float RollAttackStartRange{ 12.0f };

	// ジャンプ攻撃を開始するプレイヤーとの距離
	static constexpr float JumpAttackStartRange{ 15.0f };

	// 通常攻撃から始まった攻撃が終わった後、再び攻撃できるようになるまでの時間（秒）
	static constexpr float NormalAttackIntervalTimeSec{ 0.2f };

	// ローリング攻撃から始まった攻撃が終わった後、再び攻撃できるようになるまでの時間（秒）
	static constexpr float RollAttackIntervalTimeSec{ 0.5f };

	// ジャンプ攻撃から始まった攻撃が終わった後、再び攻撃できるようになるまでの時間（秒）
	static constexpr float JumpAttackIntervalTimeSec{ 0.5f };

	// ローリング攻撃の失敗確率（割合）
	static constexpr float RollAttackMissRate{ 0.1f };

	// ローリング攻撃の最大連続成功数（この回数連続で成功した場合、次は必ず失敗する）
	static constexpr unsigned int RollAttackMissCountMax{ 5U };

private:

	float									m_attackIntervelSecTimer{ 0.0f };
	unsigned int							m_rollAttackMissCounter{ 0U };
	tktk::ComponentPtr<tktk::Transform3D>	m_selfTransform;
	tktk::ComponentPtr<tktk::Transform3D>	m_playerTransform;
};
#endif // !ACT_3D_BOSS_ENEMY_START_ATTACK_H_
