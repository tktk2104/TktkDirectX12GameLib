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

		~BasicMeshData() = default;

	public:

		// 使用しているマテリアルを更新する
		void setMaterialHandle(size_t materialSlot, size_t materialHandle);

		// シャドウマップを書き込む
		void writeShadowMap() const;

		// 通常メッシュを描画する
		void drawMesh(const MeshDrawFuncBaseArgs& baseArgs) const;

	private:

		size_t m_useVertexBufferHandle{ 0U };
		size_t m_useIndexBufferHandle{ 0U };

		size_t m_indexNum;

		MeshPrimitiveTopology m_primitiveTopology;

		std::vector<Subset> m_materialSlots;
	};
}
#endif // !BASIC_MESH_DATA_H_