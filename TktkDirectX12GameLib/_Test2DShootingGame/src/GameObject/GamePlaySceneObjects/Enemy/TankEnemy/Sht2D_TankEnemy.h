#ifndef SHT_2D_TANK_ENEMY_H_
#define SHT_2D_TANK_ENEMY_H_

#include <TktkDX12GameLib.h>

// ��ԃG�l�~�[�I�u�W�F�N�g
struct Sht2D_TankEnemy
{
	static tktk::GameObjectPtr create(const tktkMath::Vector2& position, float rotate);
};
#endif // !SHT_2D_TANK_ENEMY_H_
