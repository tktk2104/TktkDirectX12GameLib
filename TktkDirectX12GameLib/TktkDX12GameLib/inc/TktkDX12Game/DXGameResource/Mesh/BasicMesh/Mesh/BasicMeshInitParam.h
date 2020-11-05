#ifndef BASIC_MESH_INIT_PARAM_H_
#define BASIC_MESH_INIT_PARAM_H_

#include <vector>
#include "../Structs/Subset.h"
#include "../../Structs/MeshPrimitiveTopology.h"

namespace tktk
{
	// 通常メッシュを作るときに必要な情報
	struct BasicMeshInitParam
	{
		// 使う頂点バッファのハンドル
		size_t useVertexBufferHandle;

		// 使うインデックスバッファのハンドル
		size_t useIndexBufferHandle;

		// メッシュが持つインデックスの総数
		size_t indexNum;

		MeshPrimitiveTopology primitiveTopology;

		// サブセット（使用するマテリアル情報）
		std::vector<Subset> materialSlots;
	};
}
#endif // !BASIC_MESH_INIT_PARAM_H_