#ifndef ACT_3D_BOSS_ENEMY_H_
#define ACT_3D_BOSS_ENEMY_H_

#include <TktkDX12GameLib.h>

// ボスエネミーオブジェクト
struct Act3D_BossEnemy
{
	static tktk::GameObjectPtr create(const tktkMath::Vector3& position, const tktkMath::Vector3& rotation);
};
#endif // !ACT_3D_BOSS_ENEMY_H_