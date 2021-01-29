#ifndef SHT_2D_MOVE_FORWARD_H_
#define SHT_2D_MOVE_FORWARD_H_

#include <TktkDX12GameLib.h>

// �O���Ɉړ�����R���|�[�l���g
class Sht2D_MoveForward
	: public tktk::ComponentBase
{
public:

	Sht2D_MoveForward(float moveSpeedPerSec, float accelerationPerSec);

public:

	void start();
	void update();

public:

	float getMoveSpeedPerSec() const;
	void setMoveSpeedPerSec(float moveSpeed);

private:

	// ���b�̈ړ����x
	float m_moveSpeedPerSec;

	// ���b�̉������x
	float m_accelerationPerSec;

	tktk::ComponentPtr<tktk::Transform2D>			m_transform;
	tktk::ComponentPtr<tktk::InertialMovement2D>	m_inertialMovement;
};
#endif // !SHT_2D_MOVE_FORWARD_H_
