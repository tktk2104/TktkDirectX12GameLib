#ifndef BASIC_MESH_MATERIAL_DATA_H_
#define BASIC_MESH_MATERIAL_DATA_H_

/* std::unordered_map */
#include <unordered_map>

/* class member */
#include <TktkMath/Structs/Color.h>

namespace tktk
{
	struct MeshMaterialInitParam;
	class MeshMaterialAppendParam;
	struct MeshMaterialAppendParamInitParam;
	struct MeshMaterialAppendParamUpdateFuncArgs;

	// 通常メッシュのマテリアル情報を管理するクラス
	class MeshMaterialData
	{
	public:

		explicit MeshMaterialData(const MeshMaterialInitParam& initParam);

		// コピーコンストラクタ
		// ※ 「m_appendParamMap」の要素はコピーされない（void*があるため）
		MeshMaterialData(const MeshMaterialData& other);
		
		// ムーブコンストラクタ
		MeshMaterialData(MeshMaterialData&& other) noexcept;

		~MeshMaterialData();

	public:

		// 自身のマテリアル情報とグラフィックパイプラインをコマンドリストに設定する
		void setMaterialData() const;

		// このマテリアルで追加で管理する定数バッファのハンドルと値を設定する
		void addAppendParam(const MeshMaterialAppendParamInitParam& initParam);

		// このマテリアルで追加で管理する定数バッファのIDと値を更新する
		void updateAppendParam(const MeshMaterialAppendParamUpdateFuncArgs& updateFuncArgs);

	private:

		// 定数バッファのコピー用バッファを更新する
		void updateCopyBuffer() const;

	private:

		size_t			m_usePipeLineStateHandle	{ 0U };
		size_t			m_useDescriptorHeapHandle	{ 0U };
		size_t			m_createUploadBufferHandle	{ 0U };
		//tktkMath::Color	m_materialAmbient;
		//tktkMath::Color	m_materialDiffuse;
		//tktkMath::Color	m_materialSpecular;
		//tktkMath::Color	m_materialEmissive;
		//float			m_materialShiniess;

		std::unordered_map<size_t, MeshMaterialAppendParam> m_appendParamMap;
	};
}
#endif // !BASIC_MESH_MATERIAL_DATA_H_