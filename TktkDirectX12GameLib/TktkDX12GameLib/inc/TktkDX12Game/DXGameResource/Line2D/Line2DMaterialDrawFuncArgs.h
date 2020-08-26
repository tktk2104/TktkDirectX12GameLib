#ifndef LINE_2D_DRAW_FUNC_ARGS_H_
#define LINE_2D_DRAW_FUNC_ARGS_H_

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
		unsigned int		viewportHandle;

		// 使用するシザー矩形ハンドル
		unsigned int		scissorRectHandle;

		// 使用するレンダーターゲット用のディスクリプタヒープハンドル
		unsigned int		rtvDescriptorHeapHandle;

		// ワールド行列
		tktkMath::Matrix3	worldMatrix;

		// ラインの色
		tktkMath::Color		lineColor;

		// ラインを構成する頂点の配列
		std::vector<tktkMath::Vector2> lineVertexArray;
	};
}
#endif // !LINE_2D_DRAW_FUNC_ARGS_H_
