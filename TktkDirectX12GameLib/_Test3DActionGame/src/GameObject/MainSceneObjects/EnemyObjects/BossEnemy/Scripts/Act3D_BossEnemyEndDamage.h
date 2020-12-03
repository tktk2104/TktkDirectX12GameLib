#ifndef ACT_3D_BOSS_ENEMY_END_DAMAGE_H_
#define ACT_3D_BOSS_ENEMY_END_DAMAGE_H_

#include <TktkDX12GameLib.h>

// ボスエネミーのダメージ状態を終了する処理を行うコンポーネント
class Act3D_BossEnemyEndDamage
	: public tktk::ComponentBase
{
public:

	void onEnable();
	void update();

private:

	// ダメージ状態が終わるまでの時間
	static constexpr float EndDamageTimeSec{ 0.1f };

private:

	// ダメージ状態を終了する処理を行うためのタイマー
	float m_endAttackSecTimer{ 0.0f };
};
#endif // !ACT_3D_BOSS_ENEMY_END_DAMAGE_H_
