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

		explicit BasicMeshData(const BasicMeshInitParam& initParam);

		// コピーコンストラクタ
		BasicMeshData(const BasicMeshData& other);

		// ムーブコンストラクタ
		BasicMeshData(BasicMeshData&& other) noexcept;

	public:

		// 使用しているマテリアルを更新する
		void setMaterialHandle(unsigned int materialSlot, unsigned int materialHandle);

		// シャドウマップを書き込む
		void writeShadowMap() const;

		// 通常メッシュを描画する
		void drawMesh(const MeshDrawFuncBaseArgs& baseArgs) const;

	private:

		unsigned int m_useVertexBufferHandle;
		unsigned int m_useIndexBufferHandle;

		unsigned int m_indexNum;

		MeshPrimitiveTopology m_primitiveTopology;

		std::vector<Subset> m_materialSlots;
	};
}
#endif // !BASIC_MESH_DATA_H_