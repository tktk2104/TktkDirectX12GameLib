#ifndef ACT_3D_ROTATE_TO_PLAYER_IN_TIME_H_
#define ACT_3D_ROTATE_TO_PLAYER_IN_TIME_H_

#include <TktkDX12GameLib.h>

// 一定時間の間プレイヤーの方向へ回転する処理を行うコンポーネント
class Act3D_RotateToPlayerInTime
	: public tktk::ComponentBase
{
public:

	Act3D_RotateToPlayerInTime(float roteteSpeedPerSecDeg, float rotateEndTimeSec);

public:

	void start();
	void onEnable();
	void update();

private:

	// 毎秒の回転角度（度数法）
	const float	m_roteteSpeedPerSecDeg;

	// 回転を終了するまでの時間
	const float	m_rotateEndTimeSec;

	// 回転を終了する処理を行うためのタイマー
	float		m_rotateEndSecTimer{ 0.0f };
	
	// 自身の座標管理コンポーネント
	tktk::ComponentPtr<tktk::Transform3D>	m_selfTransform;

	// プレイヤーの座標管理コンポーネント
	tktk::ComponentPtr<tktk::Transform3D>	m_playerTransform;
};
#endif // !ACT_3D_ROTATE_TO_PLAYER_IN_TIME_H_