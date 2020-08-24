#ifndef MESH_PRIMITIVE_TOPOLOGY_H_
#define MESH_PRIMITIVE_TOPOLOGY_H_

#include <TktkDX12Wrapper/Includer/D3d12Includer.h>

namespace tktk
{
	// メッシュ描画の時の頂点、インデックスバッファの解釈方法
	enum class MeshPrimitiveTopology
	{
		TriangleList	= D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST,
		TriangleStrip	= D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP
	};
}
#endif // !MESH_PRIMITIVE_TOPOLOGY_H_
