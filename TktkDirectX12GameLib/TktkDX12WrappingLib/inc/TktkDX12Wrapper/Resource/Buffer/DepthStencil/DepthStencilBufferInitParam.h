#ifndef DEPTH_STENCIL_BUFFER_INIT_PARAM_H_
#define DEPTH_STENCIL_BUFFER_INIT_PARAM_H_

#include <TktkMath/Structs/Vector2.h>

namespace tktk
{
	// 深度ステンシルバッファを作る時に必要な変数
	struct DepthStencilBufferInitParam
	{
		tktkMath::Vector2	depthStencilSize;		// 深度ステンシルテクスチャの大きさ
		bool				useAsShaderResource;	// シェーダーリソースとして使用するかのフラグ
	};
}
#endif // !DEPTH_STENCIL_BUFFER_INIT_PARAM_H_