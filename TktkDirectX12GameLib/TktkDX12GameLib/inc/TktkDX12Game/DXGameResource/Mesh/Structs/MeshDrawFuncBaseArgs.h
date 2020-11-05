#ifndef MESH_DRAW_FUNC_BASE_ARGS_H_
#define MESH_DRAW_FUNC_BASE_ARGS_H_

#include <array>
#include <TktkMath/Structs/Color.h>
#include <TktkMath/Structs/Vector3.h>
#include <TktkMath/Structs/Matrix4.h>
#include "MeshTransformCbuffer.h"
#include "MeshShadowMapCBuffer.h"

namespace tktk
{
	// メッシュ描画に必要な引数
	struct MeshDrawFuncBaseArgs
	{
		// 使用するビューポートのハンドル
		size_t			viewportHandle;

		// 使用するシザー矩形のハンドル
		size_t			scissorRectHandle;

		// 使用するレンダーターゲット用のディスクリプタヒープハンドル
		size_t			rtvDescriptorHeapHandle;

		// 使用する深度ステンシル用のディスクリプタヒープハンドル
		size_t			dsvDescriptorHeapHandle;

		// 使用するライトID
		size_t			lightHandle;
	};
}
#endif // !MESH_DRAW_FUNC_BASE_ARGS_H_