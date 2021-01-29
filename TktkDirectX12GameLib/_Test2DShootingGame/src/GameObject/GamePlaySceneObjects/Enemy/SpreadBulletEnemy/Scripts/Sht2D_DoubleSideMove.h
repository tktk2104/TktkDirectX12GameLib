#ifndef SHT_2D_DOUBLE_SIDE_MOVE_H_
#define SHT_2D_DOUBLE_SIDE_MOVE_H_

#include <TktkDX12GameLib.h>

// �����ł̔����ړ��R���|�[�l���g
class Sht2D_DoubleSideMove
	: public tktk::ComponentBase
{
public:

	Sht2D_DoubleSideMove(float moveSpeedPerSec, float accelerationPerSec, float minXPos, float maxXPos);

public:

	void start();
	void update();

private:

	// ���b�̈ړ����x
	float m_moveSpeedPerSec;

	// ���b�̉������x
	float m_accelerationPerSec;

	// �����̐܂�Ԃ������W
	float m_minXPos;

	// �E���̐܂�Ԃ������W
	float m_maxXPos;

	// �ړ����s�����]���Ă��邩�̃t���O
	bool m_isInversion{ false };

	tktk::ComponentPtr<tktk::Transform2D>			m_transform;
	tktk::ComponentPtr<tktk::InertialMovement2D>	m_inertialMovement;
};
#endif // !SHT_2D_DOUBLE_SIDE_MOVE_H_