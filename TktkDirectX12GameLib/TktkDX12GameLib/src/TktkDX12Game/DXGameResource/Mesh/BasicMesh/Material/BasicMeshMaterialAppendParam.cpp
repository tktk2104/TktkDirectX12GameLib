#include "TktkDX12Game/DXGameResource/Mesh/BasicMesh/Material/BasicMeshMaterialAppendParam.h"

#include "TktkDX12Game/_MainManager/DX12GameManager.h"

namespace tktk
{
	BasicMeshMaterialAppendParam::BasicMeshMaterialAppendParam(unsigned int cbufferHandle, unsigned int dataSize, void* dataTopPos)
		: m_cbufferHandle(cbufferHandle)
		, m_dataSize(dataSize)
	{
		m_dataTopPos = std::shared_ptr<void>(dataTopPos);
	}

	void BasicMeshMaterialAppendParam::updateParam(unsigned int dataSize, const void* dataTopPos)
	{
		if (m_dataSize == dataSize) memcpy(m_dataTopPos.get(), dataTopPos, dataSize);
	}

	void BasicMeshMaterialAppendParam::updateCbuffer() const
	{
		DX12GameManager::updateCbufferImpl(m_cbufferHandle, m_dataSize, m_dataTopPos.get());
	}
}