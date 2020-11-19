#ifndef ACT_3D_INPUT_TO_START_ATTACK_H_
#define ACT_3D_INPUT_TO_START_ATTACK_H_

#include <TktkDX12GameLib.h>

class Act3D_InputToStartAttack
	: public tktk::ComponentBase
{
public:

	Act3D_InputToStartAttack() = default;

public:

	void update();
};
#endif // !ACT_3D_INPUT_TO_START_ATTACK_H_