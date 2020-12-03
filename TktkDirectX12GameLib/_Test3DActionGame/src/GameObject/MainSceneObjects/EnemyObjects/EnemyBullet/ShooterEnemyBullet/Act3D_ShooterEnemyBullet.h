#ifndef ACT_3D_SHOOTER_ENEMY_BULLET_H_
#define ACT_3D_SHOOTER_ENEMY_BULLET_H_

#include <TktkDX12GameLib.h>

// 射撃エネミーの弾
struct Act3D_ShooterEnemyBullet
{
	static tktk::GameObjectPtr create(const tktkMath::Vector3& position, const tktkMath::Vector3& velocityPerSec);
};
#endif // !ACT_3D_SHOOTER_ENEMY_BULLET_H_