#ifndef SHT_2D_PLAYER_NORMAL_BULLET_H_
#define SHT_2D_PLAYER_NORMAL_BULLET_H_

#include <TktkDX12GameLib.h>

// プレイヤー通常弾オブジェクト
struct Sht2D_PlayerNormalBullet
{
	static tktk::GameObjectPtr create(const tktkMath::Vector2& position, float rotate, float moveSpeedPerSec);
};
#endif // !SHT_2D_PLAYER_NORMAL_BULLET_H_