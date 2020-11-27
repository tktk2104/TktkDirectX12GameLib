#ifndef ACT_3D_ROTATE_TO_PLAYER_H_
#define ACT_3D_ROTATE_TO_PLAYER_H_

#include <TktkDX12GameLib.h>

// プレイヤーの方へ回転する処理を行うコンポーネント
class Act3D_RotateToPlayer
	: public tktk::ComponentBase
{
public:

	explicit Act3D_RotateToPlayer(float roteteSpeedPerSecDeg);

public:

	void start();
	void update();

private:

	// 毎秒の回転角度（度数法）
	float									m_roteteSpeedPerSecDeg;

	// 自身の座標管理コンポーネント
	tktk::ComponentPtr<tktk::Transform3D>	m_selfTransform;

	// プレイヤーの座標管理コンポーネント
	tktk::ComponentPtr<tktk::Transform3D>	m_playerTransform;
};
#endif // !ACT_3D_ROTATE_TO_PLAYER_H_