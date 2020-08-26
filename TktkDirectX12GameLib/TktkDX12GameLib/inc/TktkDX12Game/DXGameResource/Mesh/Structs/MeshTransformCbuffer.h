#ifndef MESH_TRANSFORM_CBUFFER_H_
#define MESH_TRANSFORM_CBUFFER_H_

#include <TktkMath/Structs/Matrix4.h>

namespace tktk
{
	// メッシュの座標変換用の定数バッファ
	struct MeshTransformCbuffer
	{
		// ワールド行列
		tktkMath::Matrix4	worldMatrix		{ tktkMath::Matrix4_v::identity };

		// ビュー行列
		tktkMath::Matrix4	viewMatrix		{ tktkMath::Matrix4_v::identity };

		// プロジェクション行列
		tktkMath::Matrix4	projectionMatrix{ tktkMath::Matrix4_v::identity };
	};
}
#endif // !MESH_TRANSFORM_CBUFFER_H_