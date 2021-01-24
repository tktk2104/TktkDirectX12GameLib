#ifndef SHT_2D_ENEMY_NORMAL_BULLET_COLLISION_REACTION_H_
#define SHT_2D_ENEMY_NORMAL_BULLET_COLLISION_REACTION_H_

#include <TktkDX12GameLib.h>

class Sht2D_EnemyNormalBulletCollisionReaction
	: public tktk::ComponentBase
{
public:

	Sht2D_EnemyNormalBulletCollisionReaction() = default;

public:

	void onCollisionEnter(const tktk::GameObjectPtr & other);
};
#endif // !SHT_2D_ENEMY_NORMAL_BULLET_COLLISION_REACTION_H_