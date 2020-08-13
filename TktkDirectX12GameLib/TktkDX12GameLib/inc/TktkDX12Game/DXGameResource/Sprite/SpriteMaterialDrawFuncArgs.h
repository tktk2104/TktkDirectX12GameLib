#ifndef SPRITE_MATERIAL_DRAW_FUNC_ARGS_H_
#define SPRITE_MATERIAL_DRAW_FUNC_ARGS_H_

#include <TktkMath/Structs/Matrix3.h>

namespace tktk
{
	// スプライトのマテリアルを描画する時に必要な引数
	struct SpriteMaterialDrawFuncArgs
	{
		// 使用するビューポートID
		unsigned int		viewportId;

		// 使用するシザー矩形ID
		unsigned int		scissorRectId;

		// 使用するレンダーターゲット用のディスクリプタヒープID
		unsigned int		rtvDescriptorHeapId;

		// ワールド行列
		tktkMath::Matrix3	worldMatrix;
	};
}
#endif // !SPRITE_MATERIAL_DRAW_FUNC_ARGS_H_