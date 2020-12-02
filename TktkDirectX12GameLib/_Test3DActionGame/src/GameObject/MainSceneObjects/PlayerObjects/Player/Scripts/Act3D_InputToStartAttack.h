#ifndef ACT_3D_INPUT_TO_START_ATTACK_H_
#define ACT_3D_INPUT_TO_START_ATTACK_H_

#include <TktkDX12GameLib.h>

// ���͂ɂ���čU�����J�n����R���|�[�l���g
class Act3D_InputToStartAttack
	: public tktk::ComponentBase
{
public:

	Act3D_InputToStartAttack() = default;

public:

	void update();

private:

	// �U���̃C���^�[�o��
	constexpr static float AttackIntervalTimeSec{ 0.7f };

private:

	// �U���Ԋu���Ǘ�����R���|�[�l���g
	float m_attackIntervelSecTimer{ 0.0f };
};
#endif // !ACT_3D_INPUT_TO_START_ATTACK_H_