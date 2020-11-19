#ifndef ACT_3D_BOSS_ENEMY_START_CHASE_H_
#define ACT_3D_BOSS_ENEMY_START_CHASE_H_

#include <TktkDX12GameLib.h>

class Act3D_BossEnemyStartChase
	: public tktk::ComponentBase
{
public:

	Act3D_BossEnemyStartChase() = default;

public:

	void start();
	void update();

private:

	// プレイヤーを発見できる距離
	static constexpr float FindPlayerRange{ 20.0f };

	// プレイヤーを発見できる“真上から見た「エネミーの正面ベクトルと、プレイヤー方向のベクトル」の間の角”の最大値（度数法）
	static constexpr float FindPlayerAngleDeg{ 120.0f };

private:

	tktk::ComponentPtr<tktk::Transform3D>	m_selfTransform;
	tktk::ComponentPtr<tktk::Transform3D>	m_playerTransform;
};
#endif // !ACT_3D_BOSS_ENEMY_START_CHASE_H_
