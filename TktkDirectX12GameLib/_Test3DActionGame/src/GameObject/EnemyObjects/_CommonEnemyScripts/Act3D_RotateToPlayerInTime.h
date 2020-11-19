#ifndef ACT_3D_ROTATE_TO_PLAYER_IN_TIME_H_
#define ACT_3D_ROTATE_TO_PLAYER_IN_TIME_H_

#include <TktkDX12GameLib.h>

class Act3D_RotateToPlayerInTime
	: public tktk::ComponentBase
{
public:

	Act3D_RotateToPlayerInTime(float roteteSpeedPerSecDeg, float rotateEndTimeSec);

public:

	void start();
	void onEnable();
	void update();

private:

	const float	m_roteteSpeedPerSecDeg;
	const float	m_rotateEndTimeSec;
	float		m_rotateEndSecTimer{ 0.0f };
	
	tktk::ComponentPtr<tktk::Transform3D>	m_selfTransform;
	tktk::ComponentPtr<tktk::Transform3D>	m_playerTransform;
};
#endif // !ACT_3D_ROTATE_TO_PLAYER_IN_TIME_H_