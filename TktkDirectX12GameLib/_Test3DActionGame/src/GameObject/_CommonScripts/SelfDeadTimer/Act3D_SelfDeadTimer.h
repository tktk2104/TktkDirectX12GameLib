#ifndef ACT_3D_SELF_DEAD_TIMER_H_
#define ACT_3D_SELF_DEAD_TIMER_H_

#include <TktkDX12GameLib.h>

class Act3D_SelfDeadTimer
	: public tktk::ComponentBase
{
public:

	explicit Act3D_SelfDeadTimer(float deadTimeSec);

public:

	void start();
	void update();

private:

	const float				m_deadTimeSec;

	float					m_deadSecTimer{ 0.0f };
};
#endif // !ACT_3D_SELF_DEAD_TIMER_H_