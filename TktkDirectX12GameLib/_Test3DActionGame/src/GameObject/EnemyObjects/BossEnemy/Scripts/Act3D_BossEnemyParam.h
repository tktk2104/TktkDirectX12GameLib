#ifndef ACT_3D_BOSS_ENEMY_PARAM_H_
#define ACT_3D_BOSS_ENEMY_PARAM_H_

#include <TktkDX12GameLib.h>

class Act3D_BossEnemyParam
	: public tktk::ComponentBase
{
public:

	Act3D_BossEnemyParam() = default;

public:

	void damage(int damage);

	bool outOfHp() const;

public:

	// ç≈ëÂHP
	constexpr int getMaxHp() const { return 15; }

private:

	int m_curHp{ getMaxHp() };
};
#endif // !ACT_3D_BOSS_ENEMY_PARAM_H_