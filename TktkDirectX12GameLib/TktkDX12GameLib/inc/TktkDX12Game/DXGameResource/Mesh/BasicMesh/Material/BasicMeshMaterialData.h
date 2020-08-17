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

		BasicMeshMaterialData(const BasicMeshMaterialInitParam& initParam);
		BasicMeshMaterialData(const BasicMeshMaterialData* other);
		~BasicMeshMaterialData() = default;

	public:

		// 自身のマテリアル情報とグラフィックパイプラインをコマンドリストに設定する
		void setMaterialData() const;

		// このマテリアルで追加で管理する定数バッファのIDと値を設定する
		void addAppendParam(unsigned int cbufferId, unsigned int dataSize, void* dataTopPos);

		// このマテリアルで追加で管理する定数バッファのIDと値を更新する
		void updateAppendParam(unsigned int cbufferId, unsigned int dataSize, const void* dataTopPos);

	private:

		unsigned int		m_usePipeLineStateId;
		unsigned int		m_useDescriptorHeapId;
		tktkMath::Color		m_materialAmbient;
		tktkMath::Color		m_materialDiffuse;
		tktkMath::Color		m_materialSpecular;
		tktkMath::Color		m_materialEmissive;
		float				m_materialShiniess;

		std::unordered_map<unsigned int, BasicMeshMaterialAppendParam> m_appendParamMap;
	};
}
#endif // !BASIC_MESH_MATERIAL_DATA_H_