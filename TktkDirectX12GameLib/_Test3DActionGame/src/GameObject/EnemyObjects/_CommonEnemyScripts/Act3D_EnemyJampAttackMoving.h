#ifndef ACT_3D_ENEMY_JAMP_ATTACK_MOVING_H_
#define ACT_3D_ENEMY_JAMP_ATTACK_MOVING_H_

#include <TktkDX12GameLib.h>

class Act3D_EnemyJampAttackMoving
	: public tktk::ComponentBase
{
public:

	Act3D_EnemyJampAttackMoving(
		float jumpVerticalPower,
		float jmupVerticalMoveStartTimeSec,
		float jumpHorizontalSpeedPerSec,
		float jmupHorizontalMoveTimeSec
	);

public:

	void start();
	void onEnable();
	void update();

private:

	float											m_jumpVerticalPower;
	float											m_jmupVerticalMoveStartTimeSec;
	float											m_jumpHorizontalSpeedPerSec;
	float											m_jmupHorizontalMoveTimeSec;
	float											m_verticalMoveSecTimer		{ 0.0f };
	bool											m_afterVerticalMove			{ false };
	float											m_horizontalMoveSecTimer	{ 0.0f };
	tktk::ComponentPtr<tktk::Transform3D>			m_transform;
	tktk::ComponentPtr<tktk::InertialMovement3D>	m_inertialMovement;
};
#endif // !ACT_3D_ENEMY_JAMP_ATTACK_MOVING_H_