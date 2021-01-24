#ifndef SHT_2D_DAMAGE_POWER_H_
#define SHT_2D_DAMAGE_POWER_H_

#include <TktkDX12GameLib.h>

class Sht2D_DamagePower
	: public tktk::ComponentBase
{
public:

	Sht2D_DamagePower(float startHitPower, float stayHitPowerPerSec);

public:

	float getStartHitPower() const;

	float getStayHitPowerPerSec() const;

private:

	float m_startHitPower;
	float m_stayHitPowerPerSec;
};
#endif // !SHT_2D_DAMAGE_POWER_H_