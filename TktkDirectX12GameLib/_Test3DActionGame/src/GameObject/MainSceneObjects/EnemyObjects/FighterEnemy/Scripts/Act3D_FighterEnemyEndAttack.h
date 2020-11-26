#ifndef ACT_3D_FIGHTER_ENEMY_END_ATTACK_H_
#define ACT_3D_FIGHTER_ENEMY_END_ATTACK_H_

#include <TktkDX12GameLib.h>
#include "../../../../../Enums/Enums.h"

class Act3D_FighterEnemyEndAttack
	: public tktk::ComponentBase
{
public:

	Act3D_FighterEnemyEndAttack(float endAttackTimeSec, FighterEnemyState attackType);

public:

	void onEnable();
	void update();

private:

	const float				m_endAttackTimeSec;

	const FighterEnemyState	m_attackType;

	float					m_endAttackSecTimer{ 0.0f };
};
#endif // !ACT_3D_FIGHTER_ENEMY_END_ATTACK_H_