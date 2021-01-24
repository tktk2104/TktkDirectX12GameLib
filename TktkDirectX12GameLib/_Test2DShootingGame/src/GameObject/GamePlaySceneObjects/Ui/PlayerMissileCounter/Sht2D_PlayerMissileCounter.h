#ifndef SHT_2D_PLAYER_MISSILE_COUNTER_H_
#define SHT_2D_PLAYER_MISSILE_COUNTER_H_

#include <TktkDX12GameLib.h>

// プレイヤーのミサイル残数カウンタUI

struct Sht2D_PlayerMissileCounter
{
	static tktk::GameObjectPtr create(const tktkMath::Vector2& position);
};
#endif // !SHT_2D_PLAYER_MISSILE_COUNTER_H_