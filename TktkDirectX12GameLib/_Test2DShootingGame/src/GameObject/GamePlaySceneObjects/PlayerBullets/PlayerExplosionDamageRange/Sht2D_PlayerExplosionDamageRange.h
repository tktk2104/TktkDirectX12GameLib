#ifndef SHT_2D_PLAYER_EXPLOSION_DAMAGE_RANGE_H_
#define SHT_2D_PLAYER_EXPLOSION_DAMAGE_RANGE_H_

#include <TktkDX12GameLib.h>

// プレイヤーが発生させた爆発攻撃範囲オブジェクト
struct Sht2D_PlayerExplosionDamageRange
{
	static tktk::GameObjectPtr create(const tktkMath::Vector2& position, const tktkMath::Vector2& scale, float effectIntervalTimeSec, float deleteTime, float startHitPower, float stayHitPowerPerSec);
};
#endif // !SHT_2D_PLAYER_EXPLOSION_DAMAGE_RANGE_H_