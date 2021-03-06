#ifndef SPRITE_MATERIAL_DRAW_FUNC_ARGS_H_
#define SPRITE_MATERIAL_DRAW_FUNC_ARGS_H_

/* class member */
#include <TktkMath/Structs/Color.h>

namespace tktk
{
	// スプライトのマテリアルを描画する時に必要な引数
	struct SpriteMaterialDrawFuncArgs
	{
		// 使用するビューポートハンドル
		size_t			viewportHandle			;

		// 使用するシザー矩形ハンドル
		size_t			scissorRectHandle		;

		// 使用するレンダーターゲット用のディスクリプタヒープハンドル
		size_t			rtvDescriptorHeapHandle	;

		// ブレンドレート
		tktkMath::Color	blendRate				{ tktkMath::Color_v::white };
	};
}
#endif // !SPRITE_MATERIAL_DRAW_FUNC_ARGS_H_