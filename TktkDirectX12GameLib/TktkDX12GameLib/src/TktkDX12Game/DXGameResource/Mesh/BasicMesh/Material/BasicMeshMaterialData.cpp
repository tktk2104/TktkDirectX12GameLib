#include "TktkDX12Game/DXGameResource/Mesh/BasicMesh/Material/BasicMeshMaterialData.h"

#include "TktkDX12Game/_MainManager/DX12GameManager.h"
#include "TktkDX12Game/DXGameResource/Mesh/BasicMesh/Structs/BasicMeshMaterialCbuffer.h"

namespace tktk
{
	BasicMeshMaterialData::BasicMeshMaterialData(const BasicMeshMaterialInitParam& initParam)
		: m_usePipeLineStateId(initParam.usePipeLineStateId)
		, m_useDescriptorHeapId(initParam.useDescriptorHeapId)
		, m_materialAmbient(initParam.materialAmbient)
		, m_materialDiffuse(initParam.materialDiffuse)
		, m_materialSpecular(initParam.materialSpecular)
		, m_materialEmissive(initParam.materialEmissive)
		, m_materialShiniess(initParam.materialShiniess)
	{
	}

	BasicMeshMaterialData::BasicMeshMaterialData(const BasicMeshMaterialData* other)
		: m_usePipeLineStateId(other->m_usePipeLineStateId)
		, m_useDescriptorHeapId(other->m_useDescriptorHeapId)
		, m_materialAmbient(other->m_materialAmbient)
		, m_materialDiffuse(other->m_materialDiffuse)
		, m_materialSpecular(other->m_materialSpecular)
		, m_materialEmissive(other->m_materialEmissive)
		, m_materialShiniess(other->m_materialShiniess)
		, m_appendParamMap(other->m_appendParamMap)
	{
	}

	void BasicMeshMaterialData::setMaterialData() const
	{
		// マテリアルが使用するパイプラインステートを設定する
		DX12GameManager::setPipeLineState(m_usePipeLineStateId);

		// マテリアルの情報を定数バッファに書き込む
		{
			BasicMeshMaterialCbuffer materialBufferData{};

			materialBufferData.materialAmbient = m_materialAmbient;
			materialBufferData.materialDiffuse = m_materialDiffuse;
			materialBufferData.materialSpecular = m_materialSpecular;
			materialBufferData.materialEmissive = m_materialEmissive;
			materialBufferData.materialShiniess = m_materialShiniess;

			DX12GameManager::updateCBuffer(DX12GameManager::getSystemId(SystemCBufferType::BasicMeshMaterial), materialBufferData);
		}

		for (const auto& pair : m_appendParamMap)
		{
			pair.second.updateCbuffer();
		}

		// 指定のディスクリプタヒープを設定する
		DX12GameManager::setDescriptorHeap({ { DescriptorHeapType::basic, m_useDescriptorHeapId } });
	}

	void BasicMeshMaterialData::addAppendParam(unsigned int cbufferId, unsigned int dataSize, void* dataTopPos)
	{
		m_appendParamMap.emplace(
			std::piecewise_construct,
			std::forward_as_tuple(cbufferId),
			std::forward_as_tuple(cbufferId, dataSize, dataTopPos)
		);
	}

	void BasicMeshMaterialData::updateAppendParam(unsigned int cbufferId, unsigned int dataSize, const void* dataTopPos)
	{
		m_appendParamMap.at(cbufferId).updateParam(dataSize, dataTopPos);
	}
}