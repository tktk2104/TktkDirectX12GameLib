#ifndef ACT_3D_PLAYER_COLLISION_REACTION_H_
#define ACT_3D_PLAYER_COLLISION_REACTION_H_

#include <TktkDX12GameLib.h>

class Act3D_PlayerCollisionReaction
	: public tktk::ComponentBase
{
public:

	Act3D_PlayerCollisionReaction() = default;

public:

	void onCollisionEnter(const tktk::GameObjectPtr& other);
};
#endif // !ACT_3D_PLAYER_COLLISION_REACTION_H_