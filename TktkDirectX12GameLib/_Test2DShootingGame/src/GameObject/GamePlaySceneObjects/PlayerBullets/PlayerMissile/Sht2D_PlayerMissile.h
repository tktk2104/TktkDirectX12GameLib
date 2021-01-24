#ifndef SHT_2D_PLAYER_MISSILE_H_
#define SHT_2D_PLAYER_MISSILE_H_

#include <TktkDX12GameLib.h>

// プレイヤーミサイルオブジェクト
struct Sht2D_PlayerMissile
{
	static tktk::GameObjectPtr create(const tktkMath::Vector2& position, const tktkMath::Vector2& initVelocity, float rotate, float moveSpeedPerSec, float accelerationPerSec, float activeTimeSec, const tktk::GameObjectPtr& lockOnTarget);
};
#endif // !SHT_2D_PLAYER_MISSILE_H_