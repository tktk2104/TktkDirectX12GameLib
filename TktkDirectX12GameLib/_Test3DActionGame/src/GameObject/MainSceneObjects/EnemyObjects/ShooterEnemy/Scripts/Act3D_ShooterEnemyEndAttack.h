#ifndef ACT_3D_SHOOTER_ENEMY_END_ATTACK_H_
#define ACT_3D_SHOOTER_ENEMY_END_ATTACK_H_

#include <TktkDX12GameLib.h>
#include "../../../../../Enums/Enums.h"

class Act3D_ShooterEnemyEndAttack
	: public tktk::ComponentBase
{
public:

	Act3D_ShooterEnemyEndAttack(float endAttackTimeSec, ShooterEnemyStateType attackType);

public:

	void onEnable();
	void update();

private:

	const float					m_endAttackTimeSec;

	const ShooterEnemyStateType	m_attackType;

	float						m_endAttackSecTimer{ 0.0f };
};
#endif // !ACT_3D_SHOOTER_ENEMY_END_ATTACK_H_
