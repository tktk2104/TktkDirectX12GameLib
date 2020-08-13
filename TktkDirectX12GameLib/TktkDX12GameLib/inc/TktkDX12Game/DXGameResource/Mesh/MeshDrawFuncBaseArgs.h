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
		// 使用するビューポートのID
		unsigned int			viewportId;

		// 使用するシザー矩形のID
		unsigned int			scissorRectId;

		// 使用するレンダーターゲット用のディスクリプタヒープID
		unsigned int			rtvDescriptorHeapId;

		// 使用する深度ステンシル用のディスクリプタヒープID
		unsigned int			dsvDescriptorHeapId;

		// 使用するライトID
		unsigned int			lightId;

		// メッシュの座標変換情報
		MeshTransformCbuffer	transformBufferData{};

		// シャドウマップを使った描画に必要な情報
		MeshShadowMapCBuffer	shadowMapBufferData{};
	};
}
#endif // !MESH_DRAW_FUNC_BASE_ARGS_H_