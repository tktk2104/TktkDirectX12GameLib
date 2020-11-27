#ifndef ACT_3D_SHOOTER_ENEMY_END_DAMAGE_H_
#define ACT_3D_SHOOTER_ENEMY_END_DAMAGE_H_

#include <TktkDX12GameLib.h>

// 遠距離攻撃エネミーのダメージ状態を終了するコンポーネント
class Act3D_ShooterEnemyEndDamage
	: public tktk::ComponentBase
{
public:

	void onEnable();
	void update();

private:

	// ダメージ状態が終わるまでの時間
	static constexpr float EndDamageTimeSec{ 0.4f };

private:

	// ダメージ状態を終了するためのタイマー
	float m_endAttackSecTimer{ 0.0f };
};
#endif // !ACT_3D_SHOOTER_ENEMY_END_DAMAGE_H_
