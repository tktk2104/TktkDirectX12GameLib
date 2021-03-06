#ifndef SPRITE_CONSTANT_BUFFER_DATA_H_
#define SPRITE_CONSTANT_BUFFER_DATA_H_

/* class member */
#include <TktkMath/Structs/Color.h>
#include <TktkMath/Structs/Vector2.h>

namespace tktk
{
	// スプライト描画に使用する定数バッファ情報
	struct SpriteMaterialCbufferData
	{
		// ブレンドレート
		tktkMath::Color		blendRate			{ tktkMath::Color_v::white };

		// スクリーンサイズ
		tktkMath::Vector2	screenSize			{ 640.0f, 480.0f };

		// パディング
		float				pad[2]{};
	};
}
#endif // !SPRITE_CONSTANT_BUFFER_DATA_H_