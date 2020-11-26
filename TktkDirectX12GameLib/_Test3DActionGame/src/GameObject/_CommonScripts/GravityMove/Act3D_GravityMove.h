#ifndef ACT_3D_GRAVITY_MOVE_H_
#define ACT_3D_GRAVITY_MOVE_H_

#include <TktkDX12GameLib.h>

class Act3D_GravityMove
	: public tktk::ComponentBase
{
public:

	Act3D_GravityMove() = default;

public:

	void start();
	void update();

private:

	// �d��
	constexpr static float GravityPower{ 15.0f };

	// �d�͉����x�i���b�j
	constexpr static float GravityAccelerationPerSec{ 7.5f };

private:

	tktk::ComponentPtr<tktk::InertialMovement3D>	m_inertialMovement;
};
#endif // !ACT_3D_GRAVITY_MOVE_H_