#ifndef ACT_3D_SHOOTER_ENEMY_H_
#define ACT_3D_SHOOTER_ENEMY_H_

#include <TktkDX12GameLib.h>

// 遠距離攻撃エネミーオブジェクト
struct Act3D_ShooterEnemy
{
	static tktk::GameObjectPtr create(const tktkMath::Vector3& position, const tktkMath::Vector3& rotation);
};
#endif // !ACT_3D_SHOOTER_ENEMY_H_