#ifndef MESH_TRANSFORM_CBUFFER_H_
#define MESH_TRANSFORM_CBUFFER_H_

#include <TktkMath/Structs/Matrix4.h>

namespace tktk
{
	// メッシュの座標変換用の定数バッファ
	struct MeshTransformCbuffer
	{
		// ワールド行列
		tktkMath::Matrix4	worldMatrix		{ tktkMath::mat4Identity };

		// ビュー行列
		tktkMath::Matrix4	viewMatrix		{ tktkMath::mat4Identity };

		// プロジェクション行列
		tktkMath::Matrix4	projectionMatrix{ tktkMath::mat4Identity };
	};
}
#endif // !MESH_TRANSFORM_CBUFFER_H_