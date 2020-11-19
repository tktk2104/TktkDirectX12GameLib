#ifndef ACT_3D_INPUT_TO_START_COMBO_ATTACK_H_
#define ACT_3D_INPUT_TO_START_COMBO_ATTACK_H_

#include <TktkDX12GameLib.h>

class Act3D_InputToStartComboAttack
	: public tktk::ComponentBase
{
public:

	explicit Act3D_InputToStartComboAttack(float invalidInputTimeSec);

public:

	void onEnable();
	void update();

private:

	float m_invalidInputSecTimer{ 0.0f };
	float m_invalidInputTimeSec;
};
#endif // !ACT_3D_INPUT_TO_START_COMBO_ATTACK_H_