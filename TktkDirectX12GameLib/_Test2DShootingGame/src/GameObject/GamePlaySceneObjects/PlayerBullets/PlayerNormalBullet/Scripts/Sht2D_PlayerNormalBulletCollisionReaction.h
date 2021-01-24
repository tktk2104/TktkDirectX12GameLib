#ifndef SHT_2D_PLAYER_NORMAL_BULLET_COLLISION_REACTION_H_
#define SHT_2D_PLAYER_NORMAL_BULLET_COLLISION_REACTION_H_

#include <TktkDX12GameLib.h>

// �v���C���[�ʏ�e�̏Փ˔��胊�A�N�V�����R���|�[�l���g
class Sht2D_PlayerNormalBulletCollisionReaction
	: public tktk::ComponentBase
{
public:

	Sht2D_PlayerNormalBulletCollisionReaction() = default;

public:

	void onCollisionEnter(const tktk::GameObjectPtr & other);
};
#endif // !SHT_2D_PLAYER_NORMAL_BULLET_COLLISION_REACTION_H_