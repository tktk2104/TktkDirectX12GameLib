#ifndef SHT_2D_HEALTH_POINT_H_
#define SHT_2D_HEALTH_POINT_H_

#include <TktkDX12GameLib.h>

// ‘Ï‹v—Í‚ÌƒRƒ“ƒ|[ƒlƒ“ƒg
class Sht2D_HealthPoint
	: public tktk::ComponentBase
{
public:

	explicit Sht2D_HealthPoint(float maxHp);

public:

	// ˆø”‚Ì’l‚¾‚¯‘Ï‹v—Í‚ğŒ¸‚ç‚·
	void damage(float damage);

	// ‘Ï‹v—Í‚ªƒ[ƒˆÈ‰º‚©”»’è‚·‚é
	bool outOfHp() const;

	// Œ»İ‚Ì‘Ï‹v—Í‚ğæ“¾‚·‚é
	float getCurHp() const;

	// Å‘å‚Ì‘Ï‹v—Í‚ğæ“¾‚·‚é
	float getMaxHp() const;

private:

	// Å‘å‘Ï‹v—Í
	float m_maxHp;

	// Œ»İ‚Ì‘Ï‹v—Í
	float m_curHp;
};
#endif // !SHT_2D_HEALTH_POINT_H_