#ifndef ACT_3D_BOSS_ENEMY_START_CHASE_H_
#define ACT_3D_BOSS_ENEMY_START_CHASE_H_

#include <TktkDX12GameLib.h>

// ボスエネミーの移動を開始する処理を行うコンポーネント
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

	// 自身の座標管理コンポーネント
	tktk::ComponentPtr<tktk::Transform3D>	m_selfTransform;

	// プレイヤーの座標管理コンポーネント
	tktk::ComponentPtr<tktk::Transform3D>	m_playerTransform;
};
#endif // !ACT_3D_BOSS_ENEMY_START_CHASE_H_
