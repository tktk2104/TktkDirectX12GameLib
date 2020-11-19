#ifndef ACT_3D_FIGHTER_ENEMY_END_DAMAGE_H_
#define ACT_3D_FIGHTER_ENEMY_END_DAMAGE_H_

#include <TktkDX12GameLib.h>

class Act3D_FighterEnemyEndDamage
	: public tktk::ComponentBase
{
public:

	void onEnable();
	void update();

private:

	// ダメージ状態が終わるまでの時間
	static constexpr float EndDamageTimeSec{ 0.5f };

private:

	float m_endAttackSecTimer{ 0.0f };
};
#endif // !ACT_3D_FIGHTER_ENEMY_END_DAMAGE_H_