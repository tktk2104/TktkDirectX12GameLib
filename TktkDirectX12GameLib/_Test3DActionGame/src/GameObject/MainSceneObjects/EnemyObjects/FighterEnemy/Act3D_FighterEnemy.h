#ifndef ACT_3D_FIGHTER_ENEMY_H_
#define ACT_3D_FIGHTER_ENEMY_H_

#include <TktkDX12GameLib.h>

// �ߐڐ퓬�G�l�~�[�I�u�W�F�N�g
struct Act3D_FighterEnemy
{
	static tktk::GameObjectPtr create(const tktkMath::Vector3& position, const tktkMath::Vector3& rotation);
};
#endif // !ACT_3D_FIGHTER_ENEMY_H_