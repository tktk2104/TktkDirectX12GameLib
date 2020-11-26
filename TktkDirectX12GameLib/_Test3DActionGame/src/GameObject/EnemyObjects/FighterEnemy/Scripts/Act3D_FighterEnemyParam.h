#ifndef ACT_3D_FIGHTER_ENEMY_PARAM_H_
#define ACT_3D_FIGHTER_ENEMY_PARAM_H_

#include <TktkDX12GameLib.h>

class Act3D_FighterEnemyParam
	: public tktk::ComponentBase
{
public:

	Act3D_FighterEnemyParam() = default;

public:

	void damage(int damage);

	bool outOfHp() const;

public:

	// ç≈ëÂHP
	constexpr int getMaxHp() const { return 8; }

private:

	int m_curHp{ getMaxHp() };
};
#endif // !ACT_3D_FIGHTER_ENEMY_PARAM_H_