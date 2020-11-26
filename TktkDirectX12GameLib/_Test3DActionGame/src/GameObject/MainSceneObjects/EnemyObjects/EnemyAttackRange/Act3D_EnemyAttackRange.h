#ifndef ACT_3D_ENEMY_ATTACK_RANGE_H_
#define ACT_3D_ENEMY_ATTACK_RANGE_H_

#include <TktkDX12GameLib.h>

// �G�l�~�[�U���͈̓I�u�W�F�N�g
struct Act3D_EnemyAttackRange
{
	static tktk::GameObjectPtr create(const tktkMath::Vector3& position, const tktkMath::Vector3& scale);
};

#endif // !ACT_3D_ENEMY_ATTACK_RANGE_H_