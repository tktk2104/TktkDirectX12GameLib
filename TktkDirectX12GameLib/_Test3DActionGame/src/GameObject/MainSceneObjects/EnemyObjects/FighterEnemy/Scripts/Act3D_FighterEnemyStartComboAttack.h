#ifndef ACT3D_FIGHTER_ENEMY_START_COMBO_ATTACK_H_
#define ACT3D_FIGHTER_ENEMY_START_COMBO_ATTACK_H_

#include <TktkDX12GameLib.h>

// �ߐڍU���G�l�~�[�̃R���{�U�����n�߂邽�߂̏������s���R���|�[�l���g
class Act3D_FighterEnemyStartComboAttack
	: public tktk::ComponentBase
{
public:

	void onEnable();
	void update();

private:

	// �R���{�U������������܂ł̎���
	constexpr static float StartComboTimeSec{ 1.0f };

private:

	// �R���{�U�����J�n���邽�߂̃^�C�}�[
	float m_startComboSecTimer{ 0.0f };
};
#endif // !ACT3D_FIGHTER_ENEMY_START_COMBO_ATTACK_H_