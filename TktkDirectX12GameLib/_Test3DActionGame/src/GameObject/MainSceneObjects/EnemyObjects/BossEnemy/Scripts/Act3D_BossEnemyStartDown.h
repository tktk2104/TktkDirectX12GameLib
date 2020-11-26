#ifndef ACT_3D_BOSS_ENEMY_START_DOWN_H_
#define ACT_3D_BOSS_ENEMY_START_DOWN_H_

#include <TktkDX12GameLib.h>

class Act3D_BossEnemyStartDown
	: public tktk::ComponentBase
{
public:

	Act3D_BossEnemyStartDown() = default;

public:

	void onEnable();
	void update();

private:

	// É_ÉEÉìèÛë‘Ç…Ç»ÇÈÇ‹Ç≈ÇÃéûä‘
	constexpr static float StartDownTimeSec{ 2.0f };

private:

	float m_startDownSecTimer{ 0.0f };
};
#endif // !ACT_3D_BOSS_ENEMY_START_DOWN_H_
