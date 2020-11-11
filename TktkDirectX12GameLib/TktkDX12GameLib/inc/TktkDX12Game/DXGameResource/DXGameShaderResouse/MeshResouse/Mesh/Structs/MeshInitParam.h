#ifndef MESH_INIT_PARAM_H_
#define MESH_INIT_PARAM_H_

/* class member */
#include <vector>
#include "MeshPrimitiveTopology.h"

namespace tktk
{
	struct Subset;

	// メッシュを作るときに必要な情報
	struct MeshInitParam
	{
		// 使う頂点バッファのハンドル
		size_t useVertexBufferHandle;

		// 使うインデックスバッファのハンドル
		size_t useIndexBufferHandle;

		// メッシュが持つインデックスの総数
		size_t indexNum;

		// メッシュのポリゴンの頂点情報の法則
		MeshPrimitiveTopology primitiveTopology;

		// サブセット（使用するマテリアル情報）
		std::vector<Subset> materialSlots;
	};
}
#endif // !MESH_INIT_PARAM_H_