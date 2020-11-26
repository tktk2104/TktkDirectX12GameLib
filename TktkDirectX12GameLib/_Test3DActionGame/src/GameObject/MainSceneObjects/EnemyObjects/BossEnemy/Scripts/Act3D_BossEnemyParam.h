#ifndef ACT_3D_BOSS_ENEMY_PARAM_H_
#define ACT_3D_BOSS_ENEMY_PARAM_H_

#include <TktkDX12GameLib.h>

class Act3D_BossEnemyParam
	: public tktk::ComponentBase
{
public:

	Act3D_BossEnemyParam() = default;

public:

	void update();

public:

	void damage(int damage);
	bool outOfHp() const;

	bool canNormalAttack() const;
	void resetNormalAttackIntervelTimer(float time);

	bool canRollAttack() const;
	void resetRollAttackIntervelTimer(float time);

	bool canJumpAttack() const;
	void resetJumpAttackIntervelTimer(float time);

public:

	// ç≈ëÂHP
	constexpr int getMaxHp() const { return 15; }

private:

	int		m_curHp							{ getMaxHp() };
	float	m_normalAttackIntervalSecTimer	{ 0.0f };
	float	m_rollAttackIntervalSecTimer	{ 0.0f };
	float	m_jumpAttackIntervalSecTimer	{ 0.0f };
};
#endif // !ACT_3D_BOSS_ENEMY_PARAM_H_