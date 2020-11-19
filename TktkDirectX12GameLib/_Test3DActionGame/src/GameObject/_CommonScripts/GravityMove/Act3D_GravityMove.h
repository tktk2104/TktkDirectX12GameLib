#ifndef ACT_3D_GRAVITY_MOVE_H_
#define ACT_3D_GRAVITY_MOVE_H_

#include <TktkDX12GameLib.h>

class Act3D_GravityMove
	: public tktk::ComponentBase
{
public:

	explicit Act3D_GravityMove(float gravityPower);

public:

	void start();
	void update();

private:

	float m_gravityPower;

	tktk::ComponentPtr<tktk::InertialMovement3D>	m_inertialMovement;
};
#endif // !ACT_3D_GRAVITY_MOVE_H_