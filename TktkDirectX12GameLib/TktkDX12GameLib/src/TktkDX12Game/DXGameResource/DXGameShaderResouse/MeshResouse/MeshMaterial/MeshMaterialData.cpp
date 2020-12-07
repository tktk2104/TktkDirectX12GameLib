#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/MeshResouse/MeshMaterial/MeshMaterialData.h"

#include "TktkDX12Game/_MainManager/DX12GameManager.h"
#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/MeshResouse/MeshMaterial/Structs/MeshMaterialInitParam.h"
#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/MeshResouse/MeshMaterial/Structs/MeshMaterialCBufferData.h"
#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/MeshResouse/MeshMaterial/MeshMaterialAppendParam.h"
#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/MeshResouse/MeshMaterial/Structs/MeshMaterialAppendParamInitParam.h"
#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/MeshResouse/MeshMaterial/Structs/MeshMaterialAppendParamUpdateFuncArgs.h"

namespace tktk
{
	MeshMaterialData::MeshMaterialData(const MeshMaterialInitParam& initParam)
		: m_usePipeLineStateHandle(initParam.usePipeLineStateHandle)
		, m_useDescriptorHeapHandle(initParam.useDescriptorHeapHandle)
	{
	}

	MeshMaterialData::MeshMaterialData(const MeshMaterialData& other)
		: m_usePipeLineStateHandle(other.m_usePipeLineStateHandle)
		, m_useDescriptorHeapHandle(other.m_useDescriptorHeapHandle)
	{
	}

	MeshMaterialData::MeshMaterialData(MeshMaterialData&& other) noexcept
		: m_usePipeLineStateHandle(other.m_usePipeLineStateHandle)
		, m_useDescriptorHeapHandle(other.m_useDescriptorHeapHandle)
		, m_appendParamMap(std::move(other.m_appendParamMap))
	{
	}

	MeshMaterialData::~MeshMaterialData()
	{
	}

	void MeshMaterialData::setMaterialData() const
	{
		// マテリアルが使用するパイプラインステートを設定する
		DX12GameManager::setPipeLineState(m_usePipeLineStateHandle);

		for (const auto& pair : m_appendParamMap)
		{
			pair.second.updateCbuffer();
		}

		// 指定のディスクリプタヒープを設定する
		DX12GameManager::setDescriptorHeap({ { DescriptorHeapType::basic, m_useDescriptorHeapHandle } });
	}

	void MeshMaterialData::addAppendParam(const MeshMaterialAppendParamInitParam& initParam)
	{
		m_appendParamMap.emplace(
			std::piecewise_construct,
			std::forward_as_tuple(initParam.cbufferHandle),
			std::forward_as_tuple(initParam)
		);
	}

	void MeshMaterialData::updateAppendParam(const MeshMaterialAppendParamUpdateFuncArgs& updateFuncArgs)
	{
		m_appendParamMap.at(updateFuncArgs.cbufferHandle).updateParam(updateFuncArgs);
	}
}