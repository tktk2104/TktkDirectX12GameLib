#ifndef ACT_3D_ROTATE_TO_PLAYER_H_
#define ACT_3D_ROTATE_TO_PLAYER_H_

#include <TktkDX12GameLib.h>

class Act3D_RotateToPlayer
	: public tktk::ComponentBase
{
public:

	explicit Act3D_RotateToPlayer(float roteteSpeedPerSecDeg);

public:

	void start();
	void update();

private:

	float									m_roteteSpeedPerSecDeg;
	tktk::ComponentPtr<tktk::Transform3D>	m_selfTransform;
	tktk::ComponentPtr<tktk::Transform3D>	m_playerTransform;
};
#endif // !ACT_3D_ROTATE_TO_PLAYER_H_