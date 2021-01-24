#ifndef SHT_2D_FLAME_H_
#define SHT_2D_FLAME_H_

#include <TktkDX12GameLib.h>

// 炎エフェクトオブジェクト
struct Sht2D_Flame
{
	static tktk::GameObjectPtr create(const tktkMath::Vector2& position, float rotate);
};
#endif // !SHT_2D_FLAME_H_