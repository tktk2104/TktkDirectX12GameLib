#ifndef ACT_3D_SHOOTER_ENEMY_START_CHASE_H_
#define ACT_3D_SHOOTER_ENEMY_START_CHASE_H_

#include <TktkDX12GameLib.h>

// 遠距離攻撃エネミーの移動開始コンポーネント
class Act3D_ShooterEnemyStartChase
	: public tktk::ComponentBase
{
public:

	Act3D_ShooterEnemyStartChase() = default;

public:

	void start();
	void update();

private:

	// プレイヤーを発見できる距離
	static constexpr float FindPlayerRange{ 30.0f };

	// プレイヤーを発見できる“真上から見た「エネミーの正面ベクトルと、プレイヤー方向のベクトル」の間の角”の最大値（度数法）
	static constexpr float FindPlayerAngleDeg{ 100.0f };

private:

	// 自身の座標管理コンポーネント
	tktk::ComponentPtr<tktk::Transform3D>	m_selfTransform;

	// プレイヤーの座標管理コンポーネント
	tktk::ComponentPtr<tktk::Transform3D>	m_playerTransform;
};
#endif // !ACT_3D_SHOOTER_ENEMY_START_CHASE_H_
