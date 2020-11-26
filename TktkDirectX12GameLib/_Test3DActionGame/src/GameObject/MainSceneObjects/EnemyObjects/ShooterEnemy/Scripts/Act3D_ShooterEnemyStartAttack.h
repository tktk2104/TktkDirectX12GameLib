#ifndef ACT_3D_SHOOTER_ENEMY_START_ATTACK_H_
#define ACT_3D_SHOOTER_ENEMY_START_ATTACK_H_

#include <TktkDX12GameLib.h>

class Act3D_ShooterEnemyStartAttack
	: public tktk::ComponentBase
{
public:

	Act3D_ShooterEnemyStartAttack() = default;

public:

	void start();
	void update();

private:

	// 近距離攻撃を開始する“真上から見た「エネミーの正面ベクトルと、プレイヤー方向のベクトル」の間の角”の最大値（度数法）
	static constexpr float ShortRangeAttackStartAngleDeg{ 45.0f };

	// 遠距離攻撃を開始する“真上から見た「エネミーの正面ベクトルと、プレイヤー方向のベクトル」の間の角”の最大値（度数法）
	static constexpr float LongRangeAttackStartAngleDeg	{ 1.0f };

	// 近距離攻撃を開始するプレイヤーとの距離
	static constexpr float ShortRangeAttackStartRange	{ 3.0f };

	// 遠距離攻撃を開始するプレイヤーとの距離
	static constexpr float LongRangeAttackStartRange	{ 30.0f };

	// 近距離攻撃から始まった攻撃が終わった後、再び攻撃できるようになるまでの時間（秒）
	static constexpr float ShortRangeAttackIntervalTimeSec	{ 1.0f };

	// 遠距離攻撃から始まった攻撃が終わった後、再び攻撃できるようになるまでの時間（秒）
	static constexpr float LongRangeAttackIntervalTimeSec	{ 2.0f };

private:

	float									m_attackIntervelSecTimer{ 0.0f };
	tktk::ComponentPtr<tktk::Transform3D>	m_selfTransform;
	tktk::ComponentPtr<tktk::Transform3D>	m_playerTransform;
};
#endif // !ACT_3D_SHOOTER_ENEMY_START_ATTACK_H_