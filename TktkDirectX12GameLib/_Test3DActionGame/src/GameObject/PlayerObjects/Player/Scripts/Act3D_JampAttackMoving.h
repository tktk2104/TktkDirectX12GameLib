#ifndef ACT_3D_JAMP_ATTACK_MOVING_H_
#define ACT_3D_JAMP_ATTACK_MOVING_H_

#include <TktkDX12GameLib.h>

class Act3D_JampAttackMoving
	: public tktk::ComponentBase
{
public:

	Act3D_JampAttackMoving() = default;

public:

	void start();
	void onEnable();
	void update();

private:

	// ‚’¼•ûŒü‚É‚©‚¯‚éuŠÔ“I‚È—Í
	constexpr static float JumpVerticalPower			{ 4.5f };

	// ‚’¼•ûŒü‚É‰½•bŒãˆÚ“®‚·‚é‚©H
	constexpr static float JmupVerticalMoveStartTimeSec	{ 0.1f };

	// …•½•ûŒü‚É‚©‚¯‚éŒp‘±“I‚È—Íi–ˆ•bj
	constexpr static float JumpHorizontalSpeedPerSec	{ 5.0f };

	// …•½•ûŒü‚É‰½•bŠÔˆÚ“®‚·‚é‚©H
	constexpr static float JmupHorizontalMoveTimeSec	{ 1.3f };

private:

	float											m_verticalMoveSecTimer		{ 0.0f };
	bool											m_afterVerticalMove			{ false };
	float											m_horizontalMoveSecTimer	{ 0.0f };
	tktk::ComponentPtr<tktk::Transform3D>			m_transform;
	tktk::ComponentPtr<tktk::InertialMovement3D>	m_inertialMovement;
};
#endif // !ACT_3D_JAMP_ATTACK_MOVING_H_