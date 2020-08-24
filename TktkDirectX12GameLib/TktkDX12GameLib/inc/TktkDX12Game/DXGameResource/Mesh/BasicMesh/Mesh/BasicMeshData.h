#ifndef BASIC_MESH_DATA_H_
#define BASIC_MESH_DATA_H_

#include <vector>
#include "BasicMeshInitParam.h"
#include "../Structs/Subset.h"
#include "../../Structs/MeshDrawFuncBaseArgs.h"
#include "../../Structs/MeshPrimitiveTopology.h"

namespace tktk
{
	// 通常メッシュ情報を管理するクラス
	class BasicMeshData
	{
	public:

		BasicMeshData(const BasicMeshInitParam& initParam);
		BasicMeshData(const BasicMeshData* other);

	public:

		// 使用しているマテリアルを更新する
		void setMaterialId(unsigned int materialSlot, unsigned int materialId);

		// シャドウマップを書き込む
		void writeShadowMap() const;

		// 通常メッシュを描画する
		void drawMesh(const MeshDrawFuncBaseArgs& baseArgs) const;

	private:

		unsigned int m_useVertexBufferId;
		unsigned int m_useIndexBufferId;

		unsigned int m_indexNum;

		MeshPrimitiveTopology m_primitiveTopology;

		std::vector<Subset> m_materialSlots;
	};
}
#endif // !BASIC_MESH_DATA_H_