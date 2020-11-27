#ifndef ACT_3D_ENEMY_COLLISION_REACTION_H_
#define ACT_3D_ENEMY_COLLISION_REACTION_H_

#include <TktkDX12GameLib.h>

// �G�l�~�[�̏Փ˔��胊�A�N�V�����R���|�[�l���g
class Act3D_EnemyCollisionReaction
	: public tktk::ComponentBase
{
public:

	Act3D_EnemyCollisionReaction() = default;

public:

	void onCollisionEnter(const tktk::GameObjectPtr & other);
};
#endif // !ACT_3D_ENEMY_COLLISION_REACTION_H_