#ifndef SHT_2D_ENEMY_NORMAL_BULLET_H_
#define SHT_2D_ENEMY_NORMAL_BULLET_H_

#include <TktkDX12GameLib.h>

// �G�l�~�[�ʏ�e�I�u�W�F�N�g
struct Sht2D_EnemyNormalBullet
{
	static tktk::GameObjectPtr create(const tktkMath::Vector2& position, float rotate, const tktkMath::Vector2& velocity);
};
#endif // !SHT_2D_ENEMY_NORMAL_BULLET_H_