#ifndef SHT_2D_PLAYER_MOVE_SCRIPT_H_
#define SHT_2D_PLAYER_MOVE_SCRIPT_H_

#include <TktkDX12GameLib.h>

class Sht2D_PlayerMoveScript
	: public tktk::ComponentBase
{
public:

	Sht2D_PlayerMoveScript() = default;

public:

	void start();
	void update();

private:

	constexpr static float MoveSpeedPerSec{ 700.0f };

	constexpr static tktkMath::Vector2 MoveAreaLeftTopPos		{           64.0f,           64.0f };
	constexpr static tktkMath::Vector2 MoveAreaRightBottomPos	{ 1920.0f - 64.0f, 1080.0f - 64.0f };

private:

	tktk::ComponentPtr<tktk::Transform2D>			m_transform;
	tktk::ComponentPtr<tktk::InertialMovement2D>	m_inertialMovement;
};
#endif // !SHT_2D_PLAYER_MOVE_SCRIPT_H_