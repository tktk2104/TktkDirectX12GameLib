#ifndef SHT_2D_PLAYER_BOMB_ACTIVE_TIMER_H_
#define SHT_2D_PLAYER_BOMB_ACTIVE_TIMER_H_

#include <TktkDX12GameLib.h>

// �v���C���[�{���̃A�N�e�B�u�^�C�}�[�R���|�[�l���g
class Sht2D_PlayerBombActiveTimer
	: public tktk::ComponentBase
{
public:

	explicit Sht2D_PlayerBombActiveTimer(float activeTimeSec);

public:

	void update();

private:

	float m_activeTimeSec;
	float m_activeSecTimer{ 0.0f };
};
#endif // !SHT_2D_PLAYER_BOMB_ACTIVE_TIMER_H_