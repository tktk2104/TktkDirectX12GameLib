#ifndef ACT3D_FIGHTER_ENEMY_START_COMBO_ATTACK_H_
#define ACT3D_FIGHTER_ENEMY_START_COMBO_ATTACK_H_

#include <TktkDX12GameLib.h>

class Act3D_FighterEnemyStartComboAttack
	: public tktk::ComponentBase
{
public:

	void onEnable();
	void update();

private:

	// ÉRÉìÉ{çUåÇÇ™î≠ê∂Ç∑ÇÈÇ‹Ç≈ÇÃéûä‘
	static constexpr float StartComboTimeSec{ 1.0f };

private:

	float m_startComboSecTimer{ 0.0f };
};
#endif // !ACT3D_FIGHTER_ENEMY_START_COMBO_ATTACK_H_