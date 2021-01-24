#ifndef SHT_2D_PLAYER_BOMB_EXPLODE_H_
#define SHT_2D_PLAYER_BOMB_EXPLODE_H_

#include <TktkDX12GameLib.h>

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

	tktk::ComponentPtr<tktk::Transform2D> m_transform;

	float m_startHitPower;
	float m_stayHitPowerPerSec;
};
#endif // !SHT_2D_PLAYER_BOMB_EXPLODE_H_