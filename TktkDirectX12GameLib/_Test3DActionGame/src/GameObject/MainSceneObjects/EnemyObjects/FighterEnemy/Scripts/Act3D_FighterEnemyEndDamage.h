#ifndef ACT_3D_FIGHTER_ENEMY_END_DAMAGE_H_
#define ACT_3D_FIGHTER_ENEMY_END_DAMAGE_H_

#include <TktkDX12GameLib.h>

// 近距離攻撃エネミーのダメージ処理を終了する処理を行うコンポーネント
class Act3D_FighterEnemyEndDamage
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
#endif // !ACT_3D_FIGHTER_ENEMY_END_DAMAGE_H_