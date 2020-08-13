#ifndef MESH_SHADOW_MAP_CBUFFER_H_
#define MESH_SHADOW_MAP_CBUFFER_H_

#include <TktkMath/Structs/Matrix4.h>

namespace tktk
{
	// シャドウマップを使った描画に必要な情報
	struct MeshShadowMapCBuffer
	{
		// シャドウマップ描画に使用したビュープロジェクション行列
		tktkMath::Matrix4	shadowMapViewProjMat	{ tktkMath::mat4Identity };
	};
}
#endif // !MESH_SHADOW_MAP_CBUFFER_H_