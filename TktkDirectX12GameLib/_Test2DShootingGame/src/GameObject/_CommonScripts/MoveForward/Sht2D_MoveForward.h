#ifndef SHT_2D_MOVE_FORWARD_H_
#define SHT_2D_MOVE_FORWARD_H_

#include <TktkDX12GameLib.h>

// 前方に移動するコンポーネント
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

	// 毎秒の移動速度
	float m_moveSpeedPerSec;

	// 毎秒の加速速度
	float m_accelerationPerSec;

	tktk::ComponentPtr<tktk::Transform2D>			m_transform;
	tktk::ComponentPtr<tktk::InertialMovement2D>	m_inertialMovement;
};
#endif // !SHT_2D_MOVE_FORWARD_H_
