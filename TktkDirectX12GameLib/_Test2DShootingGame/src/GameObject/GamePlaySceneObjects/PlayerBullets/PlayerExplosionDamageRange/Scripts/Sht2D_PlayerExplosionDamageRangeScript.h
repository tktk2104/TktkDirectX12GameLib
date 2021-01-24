#ifndef SHT_2D_PLAYER_EXPLOSION_DAMAGE_RANGE_SCRIPT_H_
#define SHT_2D_PLAYER_EXPLOSION_DAMAGE_RANGE_SCRIPT_H_

#include <TktkDX12GameLib.h>

class Sht2D_PlayerExplosionDamageRangeScript
	: public tktk::ComponentBase
{
public:

	explicit Sht2D_PlayerExplosionDamageRangeScript(float deadTimeSec);
	~Sht2D_PlayerExplosionDamageRangeScript() = default;

public:

	// ñàÉtÉåÅ[ÉÄåƒÇŒÇÍÇÈ
	void update();

private:

	float m_deadTimeSec;
	float m_deadSecTimer{ 0.0f };
};
#endif // !SHT_2D_PLAYER_EXPLOSION_DAMAGE_RANGE_SCRIPT_H_