#ifndef SHT_2D_PLAYER_COLLISION_REACTION_H_
#define SHT_2D_PLAYER_COLLISION_REACTION_H_

#include <TktkDX12GameLib.h>

// プレイヤーの衝突判定リアクションコンポーネント
class Sht2D_PlayerCollisionReaction
	: public tktk::ComponentBase
{
public:

	Sht2D_PlayerCollisionReaction() = default;

public:

	void update();
	void onCollisionEnter(const tktk::GameObjectPtr & other);
	void onCollisionStay(const tktk::GameObjectPtr & other);

private:

	constexpr static float CreateExplosionIntervalTimeSec{ 0.5f };

private:

	float m_createExplosionIntervalSecTimer{ 0.0f };
};
#endif // !SHT_2D_PLAYER_COLLISION_REACTION_H_
