#ifndef EXPLOSION_2D_SCRIPT_H_
#define EXPLOSION_2D_SCRIPT_H_

#include <TktkDX12GameLib.h>

class Sht2D_ExplosionScript
	: public tktk::ComponentBase
{
public:

	explicit Sht2D_ExplosionScript(float effectEndTimeSec);
	~Sht2D_ExplosionScript() = default;

public:

	// –ˆƒtƒŒ[ƒ€ŒÄ‚Î‚ê‚é
	void update();

private:

	float m_effectEndTimeSec;
	float m_effectEndSecTimer	{ 0.0f };
};
#endif // !EXPLOSION_2D_SCRIPT_H_