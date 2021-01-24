#ifndef SHT_2D_EXPLOSION_H_
#define SHT_2D_EXPLOSION_H_

#include <TktkDX12GameLib.h>

// ２次元の爆発エフェクトを作るための構造体
struct Sht2D_Explosion
{
	// 引数に座標を渡して２次元の爆発エフェクトを作る
	static tktk::GameObjectPtr create(
		const tktkMath::Vector2& position,
		const tktkMath::Vector2& posRandomRange,
		float intervalTimeSec,
		int totalNum,
		float effectEndTimeSec
	);
};
#endif // !SHT_2D_EXPLOSION_H_