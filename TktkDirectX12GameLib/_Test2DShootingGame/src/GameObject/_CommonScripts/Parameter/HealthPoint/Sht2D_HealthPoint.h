#ifndef SHT_2D_HEALTH_POINT_H_
#define SHT_2D_HEALTH_POINT_H_

#include <TktkDX12GameLib.h>

class Sht2D_HealthPoint
	: public tktk::ComponentBase
{
public:

	explicit Sht2D_HealthPoint(float maxHp);

public:

	// ˆø”‚Ì’l‚¾‚¯HP‚ğŒ¸‚ç‚·
	void damage(float damage);

	// HP‚ªƒ[ƒˆÈ‰º‚©”»’è‚·‚é
	bool outOfHp() const;

	// Œ»İ‚ÌHP‚ğæ“¾‚·‚é
	float getCurHp() const;

	// Å‘å‚ÌHP‚ğæ“¾‚·‚é
	float getMaxHp() const;

private:

	float m_maxHp;

	float m_curHp;
};
#endif // !SHT_2D_HEALTH_POINT_H_