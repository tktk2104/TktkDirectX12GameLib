#ifndef ACT_3D_PLAYER_CONTROLLER_H_
#define ACT_3D_PLAYER_CONTROLLER_H_

#include <TktkDX12GameLib.h>

class Act3D_PlayerController
	: public tktk::ComponentBase
{
public:

	Act3D_PlayerController(float moveSpeedPerSec, float rotateDegSpeedPerSec);

public:

	void start();
	void update();

private:

	float m_moveSpeedPerSec;
	float m_rotateDegSpeedPerSec;

	tktk::ComponentPtr<tktk::Transform3D>			m_transform;
};
#endif // !ACT_3D_PLAYER_CONTROLLER_H_