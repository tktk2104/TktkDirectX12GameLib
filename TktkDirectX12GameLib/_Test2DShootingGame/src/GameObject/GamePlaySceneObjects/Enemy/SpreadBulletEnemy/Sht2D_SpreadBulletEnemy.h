#ifndef SHT_2D_SPREAD_BULLET_ENEMY_H_
#define SHT_2D_SPREAD_BULLET_ENEMY_H_

#include <TktkDX12GameLib.h>

struct Sht2D_SpreadBulletEnemy
{
	static tktk::GameObjectPtr create(const tktkMath::Vector2& position, float rotate);
};
#endif // !SHT_2D_SPREAD_BULLET_ENEMY_H_