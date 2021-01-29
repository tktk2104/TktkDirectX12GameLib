#ifndef SHT_2D_DOUBLE_SIDE_MOVE_H_
#define SHT_2D_DOUBLE_SIDE_MOVE_H_

#include <TktkDX12GameLib.h>

// ｘ軸での反復移動コンポーネント
class Sht2D_DoubleSideMove
	: public tktk::ComponentBase
{
public:

	Sht2D_DoubleSideMove(float moveSpeedPerSec, float accelerationPerSec, float minXPos, float maxXPos);

public:

	void start();
	void update();

private:

	// 毎秒の移動速度
	float m_moveSpeedPerSec;

	// 毎秒の加速速度
	float m_accelerationPerSec;

	// 左側の折り返しｘ座標
	float m_minXPos;

	// 右側の折り返しｘ座標
	float m_maxXPos;

	// 移動横行が反転しているかのフラグ
	bool m_isInversion{ false };

	tktk::ComponentPtr<tktk::Transform2D>			m_transform;
	tktk::ComponentPtr<tktk::InertialMovement2D>	m_inertialMovement;
};
#endif // !SHT_2D_DOUBLE_SIDE_MOVE_H_