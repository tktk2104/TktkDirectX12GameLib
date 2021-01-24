#ifndef SHT_2D_PLAYER_NORMAL_BULLET_COLLISION_REACTION_H_
#define SHT_2D_PLAYER_NORMAL_BULLET_COLLISION_REACTION_H_

#include <TktkDX12GameLib.h>

// プレイヤー通常弾の衝突判定リアクションコンポーネント
class Sht2D_PlayerNormalBulletCollisionReaction
	: public tktk::ComponentBase
{
public:

	Sht2D_PlayerNormalBulletCollisionReaction() = default;

public:

	void onCollisionEnter(const tktk::GameObjectPtr & other);
};
#endif // !SHT_2D_PLAYER_NORMAL_BULLET_COLLISION_REACTION_H_