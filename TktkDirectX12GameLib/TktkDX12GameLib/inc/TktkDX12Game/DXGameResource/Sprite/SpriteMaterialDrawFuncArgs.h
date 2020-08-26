#ifndef SPRITE_MATERIAL_DRAW_FUNC_ARGS_H_
#define SPRITE_MATERIAL_DRAW_FUNC_ARGS_H_

#include <TktkMath/Structs/Matrix3.h>

namespace tktk
{
	// スプライトのマテリアルを描画する時に必要な引数
	struct SpriteMaterialDrawFuncArgs
	{
		// 使用するビューポートハンドル
		unsigned int		viewportHandle;

		// 使用するシザー矩形ハンドル
		unsigned int		scissorRectHandle;

		// 使用するレンダーターゲット用のディスクリプタヒープハンドル
		unsigned int		rtvDescriptorHeapHandle;

		// ワールド行列
		tktkMath::Matrix3	worldMatrix;
	};
}
#endif // !SPRITE_MATERIAL_DRAW_FUNC_ARGS_H_