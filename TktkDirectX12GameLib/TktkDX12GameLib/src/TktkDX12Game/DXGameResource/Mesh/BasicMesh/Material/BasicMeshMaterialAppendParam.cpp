#include "TktkDX12Game/DXGameResource/Mesh/BasicMesh/Material/BasicMeshMaterialAppendParam.h"

#include "TktkDX12Game/_MainManager/DX12GameManager.h"

namespace tktk
{
	BasicMeshMaterialAppendParam::BasicMeshMaterialAppendParam(unsigned int cbufferId, unsigned int dataSize, void* dataTopPos)
		: m_cbufferId(cbufferId)
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
		DX12GameManager::updateCbufferImpl(m_cbufferId, m_dataSize, m_dataTopPos.get());
	}
}