#ifndef ACT_3D_PLAYER_PARAM_H_
#define ACT_3D_PLAYER_PARAM_H_

#include <TktkDX12GameLib.h>

class Act3D_PlayerParam
	: public tktk::ComponentBase
{
public:

	Act3D_PlayerParam() = default;

public:

	void damage(int damage);

	bool outOfHp() const;

	int getCurHp() const;

public:

	// ç≈ëÂHP
	constexpr int getMaxHp() const { return 10; }

private:

	int m_curHp{ getMaxHp() };
};
#endif // !ACT_3D_PLAYER_PARAM_H_