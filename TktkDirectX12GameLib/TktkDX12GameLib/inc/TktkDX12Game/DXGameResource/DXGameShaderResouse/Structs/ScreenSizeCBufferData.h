#ifndef DRAW_GAME_AREA_SIZE_CBUFFER_DATA_H_
#define DRAW_GAME_AREA_SIZE_CBUFFER_DATA_H_

/* class member */
#include <TktkMath/Structs/Vector2.h>

namespace tktk
{
	// スクリーンサイズの定数バッファの情報
	struct DrawGameAreaSizeCBufferData
	{
		// ゲーム描画エリアサイズ
		tktkMath::Vector2	drawGameAreaSize	{ 640.0f, 480.0f };

		// パディング
		float				pad[2]				{  };
	};
}
#endif // !DRAW_GAME_AREA_SIZE_CBUFFER_DATA_H_