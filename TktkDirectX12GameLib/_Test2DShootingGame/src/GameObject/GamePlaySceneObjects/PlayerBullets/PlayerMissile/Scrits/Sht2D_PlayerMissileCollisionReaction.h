#ifndef SHT_2D_PLAYER_MISSILE_COLLISION_REACTION_H_
#define SHT_2D_PLAYER_MISSILE_COLLISION_REACTION_H_

#include <TktkDX12GameLib.h>

#include "Sht2D_PlayerMissileExplode.h"

// �v���C���[�~�T�C���̏Փ˔��胊�A�N�V�����R���|�[�l���g
class Sht2D_PlayerMissileCollisionReaction
	: public tktk::ComponentBase
{
public:

	Sht2D_PlayerMissileCollisionReaction() = default;

public:

	void start();
	void onCollisionEnter(const tktk::GameObjectPtr& other);

private:

	tktk::ComponentPtr<Sht2D_PlayerMissileExplode> m_playerMissileExplode;
};
#endif // !SHT_2D_PLAYER_MISSILE_COLLISION_REACTION_H_