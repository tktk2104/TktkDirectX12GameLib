#ifndef MESH_INIT_PARAM_H_
#define MESH_INIT_PARAM_H_

/* class member */
#include <vector>
#include <TktkDX12Wrapper/_BaseObjects/PrimitiveTopology.h>
#include <TktkDX12Wrapper/Resource/Buffer/Vertex/VertexDataCarrier.h>

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
		PrimitiveTopology primitiveTopology;

		// サブセット（使用するマテリアル情報）
		std::vector<Subset> materialSlots;

		// インスタンス描画時、インスタンス毎の頂点バッファ情報
		VertexDataCarrier instanceVertParam { 0U, 0U, nullptr };
	};
}
#endif // !MESH_INIT_PARAM_H_