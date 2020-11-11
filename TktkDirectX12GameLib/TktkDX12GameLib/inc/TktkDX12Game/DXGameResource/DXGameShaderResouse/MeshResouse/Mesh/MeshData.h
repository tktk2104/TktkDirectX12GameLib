#ifndef MESH_DATA_H_
#define MESH_DATA_H_

/* class member */
#include <vector>
#include "Structs/MeshPrimitiveTopology.h"

namespace tktk
{
	struct MeshInitParam;
	struct Subset;
	struct MeshDrawFuncBaseArgs;

	// 通常メッシュ情報を管理するクラス
	class MeshData
	{
	public:

		explicit MeshData(const MeshInitParam& initParam);

		// コピーコンストラクタ
		MeshData(const MeshData& other);

		// ムーブコンストラクタ
		MeshData(MeshData&& other) noexcept;

		~MeshData() = default;

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
#endif // !MESH_DATA_H_