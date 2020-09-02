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
		unsigned int			viewportHandle;

		// 使用するシザー矩形のハンドル
		unsigned int			scissorRectHandle;

		// 使用するレンダーターゲット用のディスクリプタヒープハンドル
		unsigned int			rtvDescriptorHeapHandle;

		// 使用する深度ステンシル用のディスクリプタヒープハンドル
		unsigned int			dsvDescriptorHeapHandle;

		// 使用するライトID
		unsigned int			lightHandle;
	};
}
#endif // !MESH_DRAW_FUNC_BASE_ARGS_H_