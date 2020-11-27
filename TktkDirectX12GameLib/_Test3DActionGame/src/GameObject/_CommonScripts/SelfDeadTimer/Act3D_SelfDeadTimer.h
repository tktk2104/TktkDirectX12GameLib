#ifndef ACT_3D_SELF_DEAD_TIMER_H_
#define ACT_3D_SELF_DEAD_TIMER_H_

#include <TktkDX12GameLib.h>

// 一定時間後にこのコンポーネントを持つゲームオブジェクトを殺す
class Act3D_SelfDeadTimer
	: public tktk::ComponentBase
{
public:

	explicit Act3D_SelfDeadTimer(float deadTimeSec);

public:

	void start();
	void update();

private:

	// 何秒後に殺すか？
	const float				m_deadTimeSec;

	// 殺す時間のタイマー
	float					m_deadSecTimer{ 0.0f };
};
#endif // !ACT_3D_SELF_DEAD_TIMER_H_