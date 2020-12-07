#ifndef LINE_2D_DRAW_FUNC_ARGS_H_
#define LINE_2D_DRAW_FUNC_ARGS_H_

/* class member */
#include <vector>
#include <TktkMath/Structs/Color.h>
#include <TktkMath/Structs/Vector2.h>
#include <TktkMath/Structs/Matrix3.h>

namespace tktk
{
	// ２Ｄライン描画に必要な変数
	struct Line2DMaterialDrawFuncArgs
	{
		// 使用するビューポートハンドル
		size_t		viewportHandle;

		// 使用するシザー矩形ハンドル
		size_t		scissorRectHandle;

		// 使用するレンダーターゲット用のディスクリプタヒープハンドル
		size_t		rtvDescriptorHeapHandle;

		// ワールド行列
		tktkMath::Matrix3	worldMatrix;

		// ラインの色
		tktkMath::Color		lineColor;

		// ラインを構成する頂点の配列
		std::vector<tktkMath::Vector2> lineVertexArray;
	};
}
#endif // !LINE_2D_DRAW_FUNC_ARGS_H_
