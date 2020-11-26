#ifndef ACT_3D_PLAYER_HP_BAR_H_
#define ACT_3D_PLAYER_HP_BAR_H_

#include <TktkDX12GameLib.h>

struct Act3D_PlayerHpBar
{
	static tktk::GameObjectPtr create(const tktkMath::Vector2& pos);
};
#endif // !ACT_3D_PLAYER_HP_BAR_H_