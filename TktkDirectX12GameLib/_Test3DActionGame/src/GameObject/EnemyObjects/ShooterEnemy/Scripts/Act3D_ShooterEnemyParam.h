#ifndef ACT_3D_SHOOTER_ENEMY_PARAM_H_
#define ACT_3D_SHOOTER_ENEMY_PARAM_H_

#include <TktkDX12GameLib.h>

class Act3D_ShooterEnemyParam
	: public tktk::ComponentBase
{
public:

	Act3D_ShooterEnemyParam() = default;

public:

	void damage(int damage);

	bool outOfHp() const;

public:

	// ç≈ëÂHP
	constexpr int getMaxHp() const { return 3; }

private:

	int m_curHp{ getMaxHp() };
};
#endif // !ACT_3D_SHOOTER_ENEMY_PARAM_H_
