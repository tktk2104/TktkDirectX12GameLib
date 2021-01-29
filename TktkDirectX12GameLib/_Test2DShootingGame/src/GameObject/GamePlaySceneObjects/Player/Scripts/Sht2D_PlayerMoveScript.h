#ifndef SHT_2D_PLAYER_MOVE_SCRIPT_H_
#define SHT_2D_PLAYER_MOVE_SCRIPT_H_

#include <TktkDX12GameLib.h>

// プレイヤー移動コンポーネント
class Sht2D_PlayerMoveScript
	: public tktk::ComponentBase
{
public:

	Sht2D_PlayerMoveScript() = default;

public:

	void start();
	void update();

private:

	// 毎秒の移動速度
	constexpr static float MoveSpeedPerSec		{ 700.0f };

	// 毎秒の加速速度
	constexpr static float AccelerationPerSec	{ 4096.0f };

	// 移動可能範囲の左上座標
	constexpr static tktkMath::Vector2 MoveAreaLeftTopPos		{           64.0f,           64.0f };

	// 移動可能範囲の右下座標
	constexpr static tktkMath::Vector2 MoveAreaRightBottomPos	{ 1920.0f - 64.0f, 1080.0f - 64.0f };

private:

	tktk::ComponentPtr<tktk::Transform2D>			m_transform;
	tktk::ComponentPtr<tktk::InertialMovement2D>	m_inertialMovement;
};
#endif // !SHT_2D_PLAYER_MOVE_SCRIPT_H_