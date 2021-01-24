#ifndef MESH_DATA_H_
#define MESH_DATA_H_

/* class member */
#include <array>
#include <vector>
#include <forward_list>
#include <TktkMath/Structs/Matrix4.h>
#include <TktkDX12Wrapper/_BaseObjects/PrimitiveTopology.h>
#include <TktkDX12Wrapper/Resource/Buffer/CopySourceDataCarrier.h>

namespace tktk
{
	struct MeshInitParam;
	struct Subset;
	struct MeshDrawFuncBaseArgs;

	// メッシュ情報を管理するクラス
	class MeshData
	{
	public:

		explicit MeshData(const MeshInitParam& initParam);

		// コピーコンストラクタ
		MeshData(const MeshData& other);

		// ムーブコンストラクタ
		MeshData(MeshData&& other) noexcept;

		~MeshData();

	public:

		// 使用しているマテリアルを更新する
		void setMaterialHandle(size_t materialSlot, size_t materialHandle);

		// メッシュをインスタンス描画する時に使用する値を削除する
		void clearInstanceParam();

		// メッシュをインスタンス描画する時に使用する値を追加する
		void addInstanceVertParam(const CopySourceDataCarrier& instanceParam);

		// スキニングメッシュをインスタンス描画する時に使用する骨行列を追加する
		void addInstanceBoneMatrix(const std::array<tktkMath::Matrix4, 128>& boneMatrix);

		// インスタンス描画情報を扱う頂点バッファを更新する
		void updateInstanceParamVertBuffer() const;

		// 骨情報を扱うテクスチャバッファを更新する
		void updateBoneMatrixTextureBuffer() const;

		// シャドウマップを書き込む
		void writeShadowMap() const;

		// 骨情報を使ってシャドウマップを書き込む
		void writeShadowMapUseBone() const;
		
		// メッシュをインスタンス描画する
		void draw(const MeshDrawFuncBaseArgs& baseArgs) const;

		// スキニングメッシュをインスタンス描画する
		void drawUseBone(const MeshDrawFuncBaseArgs& baseArgs) const;

	private:

		// メッシュの頂点バッファのハンドル
		size_t m_useVertexBufferHandle			{ 0U };

		// メッシュのインデックスバッファのハンドル
		size_t m_useIndexBufferHandle			{ 0U };

		// インスタンス情報を扱う頂点バッファのハンドル
		size_t m_instanceParamVertexBufferHandle{ 0U };

		// インスタンス情報を扱う頂点バッファを更新するバッファのハンドル
		size_t m_instanceParamUplaodBufferHandle{ 0U };

		// 骨情報を扱うテクスチャバッファのハンドル
		size_t m_boneMatrixTextureBufferHandle	{ 0U };

		// メッシュの総インデックス数
		size_t m_indexNum;

		// メッシュの頂点情報の形式
		PrimitiveTopology				m_primitiveTopology;

		// メッシュが使用しているマテリアルと対応するインデックス数の組み合わせの一覧
		std::vector<Subset>				m_materialSlots;

		// インスタンス描画用の頂点バッファの型のサイズ
		size_t							m_instanceVertParamTypeSize;

		// インスタンス描画する時の最大インスタンス数
		size_t							m_maxInstanceCount;

		// 一度に描画するインスタンス数
		size_t							m_instanceCount{ 0U };

		// インスタンス情報の配列
		std::forward_list<std::vector<unsigned char>>			m_instanceVertParamList;
		std::forward_list<std::array<tktkMath::Matrix4, 128U>>	m_instanceBoneMatrixList;
	};
}
#endif // !MESH_DATA_H_