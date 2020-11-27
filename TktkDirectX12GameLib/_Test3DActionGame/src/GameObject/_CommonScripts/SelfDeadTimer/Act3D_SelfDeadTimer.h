#ifndef ACT_3D_SELF_DEAD_TIMER_H_
#define ACT_3D_SELF_DEAD_TIMER_H_

#include <TktkDX12GameLib.h>

// ��莞�Ԍ�ɂ��̃R���|�[�l���g�����Q�[���I�u�W�F�N�g���E��
class Act3D_SelfDeadTimer
	: public tktk::ComponentBase
{
public:

	explicit Act3D_SelfDeadTimer(float deadTimeSec);

public:

	void start();
	void update();

private:

	// ���b��ɎE�����H
	const float				m_deadTimeSec;

	// �E�����Ԃ̃^�C�}�[
	float					m_deadSecTimer{ 0.0f };
};
#endif // !ACT_3D_SELF_DEAD_TIMER_H_