#ifndef BASIC_MESH_MATERIAL_DATA_H_
#define BASIC_MESH_MATERIAL_DATA_H_

#include <unordered_map>
#include "BasicMeshMaterialInitParam.h"
#include "../../Structs/MeshDrawFuncBaseArgs.h"
#include "BasicMeshMaterialAppendParam.h"

namespace tktk
{
	// 通常メッシュのマテリアル情報を管理するクラス
	class BasicMeshMaterialData
	{
	public:

		explicit BasicMeshMaterialData(const BasicMeshMaterialInitParam& initParam);

		// コピーコンストラクタ
		// ※ 「m_appendParamMap」の要素はコピーされない（void*があるため）
		BasicMeshMaterialData(const BasicMeshMaterialData& other);
		
		// ムーブコンストラクタ
		BasicMeshMaterialData(BasicMeshMaterialData&& other) noexcept;

		~BasicMeshMaterialData();

	public:

		// 自身のマテリアル情報とグラフィックパイプラインをコマンドリストに設定する
		void setMaterialData() const;

		// このマテリアルで追加で管理する定数バッファのハンドルと値を設定する
		void addAppendParam(size_t cbufferHandle, size_t dataSize, void* dataTopPos);

		// このマテリアルで追加で管理する定数バッファのIDと値を更新する
		void updateAppendParam(size_t cbufferHandle, size_t dataSize, const void* dataTopPos);

	private:

		// 定数バッファのコピー用バッファを更新する
		void updateCopyBuffer() const;

	private:

		size_t			m_usePipeLineStateHandle	{ 0U };
		size_t			m_useDescriptorHeapHandle	{ 0U };
		size_t			m_createUploadBufferHandle	{ 0U };
		tktkMath::Color	m_materialAmbient;
		tktkMath::Color	m_materialDiffuse;
		tktkMath::Color	m_materialSpecular;
		tktkMath::Color	m_materialEmissive;
		float			m_materialShiniess;

		std::unordered_map<size_t, BasicMeshMaterialAppendParam> m_appendParamMap;
	};
}
#endif // !BASIC_MESH_MATERIAL_DATA_H_