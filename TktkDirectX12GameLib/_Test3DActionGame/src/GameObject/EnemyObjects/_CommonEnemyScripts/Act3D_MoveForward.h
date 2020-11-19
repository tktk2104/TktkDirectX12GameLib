#ifndef ACT_3D_MOVE_FORWARD_H_
#define ACT_3D_MOVE_FORWARD_H_

#include <TktkDX12GameLib.h>

class Act3D_MoveForward
	: public tktk::ComponentBase
{
public:

	Act3D_MoveForward(float moveSpeedPerSec);

public:

	void start();
	void update();

private:

	float									m_moveSpeedPerSec;
	tktk::ComponentPtr<tktk::Transform3D>	m_selfTransform;
};
#endif // !ACT_3D_MOVE_FORWARD_H_