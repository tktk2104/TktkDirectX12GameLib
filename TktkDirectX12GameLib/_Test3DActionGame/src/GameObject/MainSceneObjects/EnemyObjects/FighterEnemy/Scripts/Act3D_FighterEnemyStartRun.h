#ifndef ACT3D_FIGHTER_ENEMY_START_RUN_H_
#define ACT3D_FIGHTER_ENEMY_START_RUN_H_

#include <TktkDX12GameLib.h>

class Act3D_FighterEnemyStartRun
	: public tktk::ComponentBase
{
public:

	void onEnable();
	void update();

private:

	// É_ÉbÉVÉÖÇ™î≠ê∂Ç∑ÇÈÇ‹Ç≈ÇÃéûä‘
	static constexpr float StartRunTimeSec{ 3.0f };

private:

	float m_startRunSecTimer{ 0.0f };
};
#endif // !ACT3D_FIGHTER_ENEMY_START_RUN_H_