#ifndef ACT_3D_ENEMY_JAMP_ATTACK_MOVING_H_
#define ACT_3D_ENEMY_JAMP_ATTACK_MOVING_H_

#include <TktkDX12GameLib.h>

class Act3D_EnemyJampAttackMoving
	: public tktk::ComponentBase
{
public:

	Act3D_EnemyJampAttackMoving(float jumpSpeedPerSec, float moveTimeSec);

public:

	void start();
	void onEnable();
	void update();

private:

	float											m_jumpSpeedPerSec;
	float											m_moveTimeSec;
	float											m_moveSecTimer{ 0.0f };
	tktk::ComponentPtr<tktk::Transform3D>			m_transform;
};
#endif // !ACT_3D_ENEMY_JAMP_ATTACK_MOVING_H_