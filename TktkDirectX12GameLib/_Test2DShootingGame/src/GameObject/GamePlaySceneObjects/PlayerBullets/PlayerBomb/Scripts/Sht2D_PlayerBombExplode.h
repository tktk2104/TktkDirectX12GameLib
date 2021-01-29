#ifndef SHT_2D_PLAYER_BOMB_EXPLODE_H_
#define SHT_2D_PLAYER_BOMB_EXPLODE_H_

#include <TktkDX12GameLib.h>

// �N���p�R���|�[�l���g
class Sht2D_PlayerBombExplode
	: public tktk::ComponentBase
{
public:

	Sht2D_PlayerBombExplode(float startHitPower, float stayHitPowerPerSec);

public:

	void start();

public:

	void explode();

private:

	// �ڐG�J�n���_���[�W
	float m_startHitPower;

	// ���b�̐ڐG���_���[�W
	float m_stayHitPowerPerSec;

	tktk::ComponentPtr<tktk::Transform2D> m_transform;
};
#endif // !SHT_2D_PLAYER_BOMB_EXPLODE_H_