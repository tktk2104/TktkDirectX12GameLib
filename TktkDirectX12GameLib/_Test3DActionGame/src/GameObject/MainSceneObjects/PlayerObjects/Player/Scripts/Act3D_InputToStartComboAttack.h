#ifndef ACT_3D_INPUT_TO_START_COMBO_ATTACK_H_
#define ACT_3D_INPUT_TO_START_COMBO_ATTACK_H_

#include <TktkDX12GameLib.h>

class Act3D_InputToStartComboAttack
	: public tktk::ComponentBase
{
public:

	explicit Act3D_InputToStartComboAttack() = default;

public:

	void onEnable();
	void update();

private:

	constexpr static float InvalidStateChangeTimeSec{ 0.45f };

private:

	float	m_invalidStateChangeSecTimer	{ 0.0f };
	bool	m_afterInput			{ false };
};
#endif // !ACT_3D_INPUT_TO_START_COMBO_ATTACK_H_