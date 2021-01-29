#ifndef SHT_2D_PLAYER_MOVE_SCRIPT_H_
#define SHT_2D_PLAYER_MOVE_SCRIPT_H_

#include <TktkDX12GameLib.h>

// �v���C���[�ړ��R���|�[�l���g
class Sht2D_PlayerMoveScript
	: public tktk::ComponentBase
{
public:

	Sht2D_PlayerMoveScript() = default;

public:

	void start();
	void update();

private:

	// ���b�̈ړ����x
	constexpr static float MoveSpeedPerSec		{ 700.0f };

	// ���b�̉������x
	constexpr static float AccelerationPerSec	{ 4096.0f };

	// �ړ��\�͈͂̍�����W
	constexpr static tktkMath::Vector2 MoveAreaLeftTopPos		{           64.0f,           64.0f };

	// �ړ��\�͈͂̉E�����W
	constexpr static tktkMath::Vector2 MoveAreaRightBottomPos	{ 1920.0f - 64.0f, 1080.0f - 64.0f };

private:

	tktk::ComponentPtr<tktk::Transform2D>			m_transform;
	tktk::ComponentPtr<tktk::InertialMovement2D>	m_inertialMovement;
};
#endif // !SHT_2D_PLAYER_MOVE_SCRIPT_H_