#ifndef ACT_3D_INPUT_TO_START_COMBO_ATTACK_H_
#define ACT_3D_INPUT_TO_START_COMBO_ATTACK_H_

#include <TktkDX12GameLib.h>

// ���͂ɂ���ē�i�ڍU�����J�n����R���|�[�l���g
class Act3D_InputToStartComboAttack
	: public tktk::ComponentBase
{
public:

	Act3D_InputToStartComboAttack() = default;

public:

	void onEnable();
	void update();

private:

	// ��i�ڍU���ւ̑J�ڂ𖳌��ɂ��鎞�ԁi�b�j
	constexpr static float InvalidStateChangeTimeSec{ 0.45f };

private:

	// ��i�ڍU���ւ̑J�ڂ𖳌��ɂ��鎞�Ԃ��Ǘ�����^�C�}�[
	float	m_invalidStateChangeSecTimer	{ 0.0f };

	// ���͌��Ԃ��̃t���O
	bool	m_afterInput			{ false };
};
#endif // !ACT_3D_INPUT_TO_START_COMBO_ATTACK_H_