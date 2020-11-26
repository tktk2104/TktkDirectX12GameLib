#ifndef ACT_3D_PLAYER_CONTROLLER_H_
#define ACT_3D_PLAYER_CONTROLLER_H_

#include <TktkDX12GameLib.h>

// プレイヤーを移動、回転させるコンポーネント
class Act3D_PlayerController
	: public tktk::ComponentBase
{
public:

	Act3D_PlayerController(float moveSpeedPerSec, float rotateDegSpeedPerSec);

public:

	void start();
	void update();
	void handleMessage(tktk::MessageTypeCarrier type, const tktk::MessageAttachment& attachment);

private:

	// 移動処理
	void move();

	// 回転処理
	void rotate();

	// 最も近い敵の方に向く
	void lookMostNearEnemy();

private:

	float m_moveSpeedPerSec;
	float m_rotateDegSpeedPerSec;

	tktk::ComponentPtr<tktk::Transform3D>	m_transform;
};
#endif // !ACT_3D_PLAYER_CONTROLLER_H_