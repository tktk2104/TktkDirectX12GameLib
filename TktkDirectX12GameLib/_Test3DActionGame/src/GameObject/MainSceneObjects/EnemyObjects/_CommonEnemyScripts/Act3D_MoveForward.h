#ifndef ACT_3D_MOVE_FORWARD_H_
#define ACT_3D_MOVE_FORWARD_H_

#include <TktkDX12GameLib.h>

// 前方に移動する処理を行うコンポーネント
class Act3D_MoveForward
	: public tktk::ComponentBase
{
public:

	explicit Act3D_MoveForward(float moveSpeedPerSec);

public:

	void start();
	void update();

private:

	// 毎秒の移動速度
	float									m_moveSpeedPerSec;

	// 座標管理コンポーネント
	tktk::ComponentPtr<tktk::Transform3D>	m_selfTransform;
};
#endif // !ACT_3D_MOVE_FORWARD_H_