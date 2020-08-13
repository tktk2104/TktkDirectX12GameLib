#ifndef LINE_2D_DRAW_FUNC_ARGS_H_
#define LINE_2D_DRAW_FUNC_ARGS_H_

#include <vector>
#include <TktkMath/Structs/Color.h>
#include <TktkMath/Structs/Vector2.h>
#include <TktkMath/Structs/Matrix3.h>

namespace tktk
{
	struct Line2DMaterialDrawFuncArgs
	{
		// 使用するビューポートID
		unsigned int		viewportId;

		// 使用するシザー矩形ID
		unsigned int		scissorRectId;

		// 使用するレンダーターゲット用のディスクリプタヒープID
		unsigned int		rtvDescriptorHeapId;

		// ワールド行列
		tktkMath::Matrix3	worldMatrix;

		// ラインの色
		tktkMath::Color		lineColor;

		// ラインを構成する頂点の配列
		std::vector<tktkMath::Vector2> lineVertexArray;
	};
}
#endif // !LINE_2D_DRAW_FUNC_ARGS_H_
