#ifndef ACT_3D_ENEMY_DELETE_TIMER_H_
#define ACT_3D_ENEMY_DELETE_TIMER_H_

#include <TktkDX12GameLib.h>

class Act3D_EnemyDeleteTimer
	: public tktk::ComponentBase
{
public:

	Act3D_EnemyDeleteTimer() = default;

public:

	void update();

private:

	constexpr static float DeleteTimeSec{ 9.0f };

private:

	float m_deleteSecTimer{ 0.0f };
};
#endif // !ACT_3D_ENEMY_DELETE_TIMER_H_
