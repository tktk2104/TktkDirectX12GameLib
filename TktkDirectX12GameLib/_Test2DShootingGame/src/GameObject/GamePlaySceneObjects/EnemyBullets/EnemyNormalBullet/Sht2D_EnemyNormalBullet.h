#ifndef SHT_2D_ENEMY_NORMAL_BULLET_H_
#define SHT_2D_ENEMY_NORMAL_BULLET_H_

#include <TktkDX12GameLib.h>

// エネミー通常弾オブジェクト
struct Sht2D_EnemyNormalBullet
{
	static tktk::GameObjectPtr create(const tktkMath::Vector2& position, float rotate, const tktkMath::Vector2& velocity);
};
#endif // !SHT_2D_ENEMY_NORMAL_BULLET_H_