#ifndef SHT_2D_DOUBLE_SIDE_MOVE_H_
#define SHT_2D_DOUBLE_SIDE_MOVE_H_

#include <TktkDX12GameLib.h>

class Sht2D_DoubleSideMove
	: public tktk::ComponentBase
{
public:

	Sht2D_DoubleSideMove(float moveSpeedPerSec, float accelerationPerSec, float minXPos, float maxXPos);

public:

	void start();
	void update();

private:

	float m_moveSpeedPerSec;
	float m_accelerationPerSec;

	float m_minXPos;
	float m_maxXPos;

	bool m_isInversion{ false };

	tktk::ComponentPtr<tktk::Transform2D>			m_transform;
	tktk::ComponentPtr<tktk::InertialMovement2D>	m_inertialMovement;
};
#endif // !SHT_2D_DOUBLE_SIDE_MOVE_H_