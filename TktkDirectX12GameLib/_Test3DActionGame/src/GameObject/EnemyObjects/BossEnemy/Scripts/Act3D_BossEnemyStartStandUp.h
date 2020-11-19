#ifndef ACT_3D_BOSS_ENEMY_START_STAND_UP_H_
#define ACT_3D_BOSS_ENEMY_START_STAND_UP_H_

#include <TktkDX12GameLib.h>

class Act3D_BossEnemyStartStandUp
	: public tktk::ComponentBase
{
public:

	Act3D_BossEnemyStartStandUp() = default;

public:

	void onEnable();
	void update();

private:

	// ‹N‚«ã‚ª‚é‚Ü‚Å‚ÌŠÔ
	constexpr static float StartStandUpTimeSec{ 5.0f };

private:

	float m_startStandUpSecTimer{ 0.0f };
};
#endif // !ACT_3D_BOSS_ENEMY_START_STAND_UP_H_