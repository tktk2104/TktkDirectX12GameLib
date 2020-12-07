#ifndef DRAW_GAME_AREA_CBUFFER_DATA_H_
#define DRAW_GAME_AREA_CBUFFER_DATA_H_

#include <TktkMath/Structs/Vector2.h>

namespace tktk
{
	// ゲームの描画エリア描画用のポストエフェクト定数バッファ
	struct DrawGameAreaCBufferData
	{
		tktkMath::Vector2 drawGameAreaSizeRate;
	};
}
#endif // !DRAW_GAME_AREA_CBUFFER_DATA_H_