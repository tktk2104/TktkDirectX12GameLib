#ifndef MESH_SHADOW_MAP_CBUFFER_DATA_H_
#define MESH_SHADOW_MAP_CBUFFER_DATA_H_

/* class member */
#include <TktkMath/Structs/Matrix4.h>

namespace tktk
{
	// シャドウマップを使った描画に必要な情報
	struct MeshShadowMapCBufferData
	{
		// シャドウマップ描画に使用したビュープロジェクション行列
		tktkMath::Matrix4	shadowMapViewProjMat	{ tktkMath::Matrix4_v::identity };
	};
}
#endif // !MESH_SHADOW_MAP_CBUFFER_DATA_H_