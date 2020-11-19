#ifndef ACT_3D_BOSS_ENEMY_END_ATTACK_H_
#define ACT_3D_BOSS_ENEMY_END_ATTACK_H_

#include <TktkDX12GameLib.h>
#include "../../../../Enums/Enums.h"

class Act3D_BossEnemyEndAttack
	: public tktk::ComponentBase
{
public:

	Act3D_BossEnemyEndAttack(float endAttackTimeSec, BossEnemyStateType attackType);

public:

	void onEnable();
	void update();

private:

	const float					m_endAttackTimeSec;

	const BossEnemyStateType	m_attackType;

	float						m_endAttackSecTimer{ 0.0f };
};
#endif // !ACT_3D_BOSS_ENEMY_END_ATTACK_H_