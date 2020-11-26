#ifndef ACT_3D_BOSS_ENEMY_END_DOWN_H_
#define ACT_3D_BOSS_ENEMY_END_DOWN_H_

#include <TktkDX12GameLib.h>

class Act3D_BossEnemyEndDown
	: public tktk::ComponentBase
{
public:

	Act3D_BossEnemyEndDown() = default;

public:

	void onEnable();
	void update();

private:

	// ‹N‚«ã‚ª‚éI‚í‚é‚Ü‚Å‚ÌŠÔ
	constexpr static float EndDownTimeSec{ 0.8f };

private:

	float m_endDownUpSecTimer{ 0.0f };
};
#endif // !ACT_3D_BOSS_ENEMY_END_DOWN_H_