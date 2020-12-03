#ifndef ACT_3D_MOVE_FORWARD_H_
#define ACT_3D_MOVE_FORWARD_H_

#include <TktkDX12GameLib.h>

// �O���Ɉړ����鏈�����s���R���|�[�l���g
class Act3D_MoveForward
	: public tktk::ComponentBase
{
public:

	explicit Act3D_MoveForward(float moveSpeedPerSec);

public:

	void start();
	void update();

private:

	// ���b�̈ړ����x
	float									m_moveSpeedPerSec;

	// ���W�Ǘ��R���|�[�l���g
	tktk::ComponentPtr<tktk::Transform3D>	m_selfTransform;
};
#endif // !ACT_3D_MOVE_FORWARD_H_