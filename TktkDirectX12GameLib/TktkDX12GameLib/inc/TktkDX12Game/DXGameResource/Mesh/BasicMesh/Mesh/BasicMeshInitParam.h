#ifndef BASIC_MESH_INIT_PARAM_H_
#define BASIC_MESH_INIT_PARAM_H_

#include <vector>
#include "../Subset.h"
#include "../../MeshPrimitiveTopology.h"

namespace tktk
{
	// 通常メッシュを作るときに必要な情報
	struct BasicMeshInitParam
	{
		// 使う頂点バッファのID
		unsigned int useVertexBufferId;

		// 使うインデックスバッファのID
		unsigned int useIndexBufferId;

		// メッシュが持つインデックスの総数
		unsigned int indexNum;

		MeshPrimitiveTopology primitiveTopology;

		// サブセット（使用するマテリアル情報）
		std::vector<Subset> materialSlots;
	};
}
#endif // !BASIC_MESH_INIT_PARAM_H_