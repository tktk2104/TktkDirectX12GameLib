#ifndef MESH_PRIMITIVE_TOPOLOGY_H_
#define MESH_PRIMITIVE_TOPOLOGY_H_

namespace tktk
{
	// メッシュ描画の時の頂点、インデックスバッファの解釈方法
	enum class MeshPrimitiveTopology
	{
		TriangleList	= 4,
		TriangleStrip	= 5
	};
}
#endif // !MESH_PRIMITIVE_TOPOLOGY_H_
