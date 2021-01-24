#ifndef SHT_2D_PLAYER_BOMB_COLLISION_REACTION_H_
#define SHT_2D_PLAYER_BOMB_COLLISION_REACTION_H_

#include <TktkDX12GameLib.h>

#include "Sht2D_PlayerBombExplode.h"

// �v���C���[�{���̏Փ˔��胊�A�N�V�����R���|�[�l���g
class Sht2D_PlayerBombCollisionReaction
	: public tktk::ComponentBase
{
public:

	Sht2D_PlayerBombCollisionReaction() = default;

public:

	void start();
	void onCollisionEnter(const tktk::GameObjectPtr& other);

private:

	tktk::ComponentPtr<Sht2D_PlayerBombExplode> m_playerBombExplode;
};
#endif // !SHT_2D_PLAYER_BOMB_COLLISION_REACTION_H_
