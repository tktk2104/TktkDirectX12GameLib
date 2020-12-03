#include "TktkDX12Wrapper/Resource/Buffer/Constant/ConstantBuffer.h"

namespace tktk
{
	ConstantBuffer::ConstantBuffer(const tktkContainer::ResourceContainerInitParam& initParam)
		: m_constantBufferDataArray(initParam)
	{
	}

	size_t ConstantBuffer::create(ID3D12Device* device, const CopySourceDataCarrier& constantBufferData)
	{
		return m_constantBufferDataArray.create(device, constantBufferData);
	}

	void ConstantBuffer::erase(size_t handle)
	{
		m_constantBufferDataArray.erase(handle);
	}

	void ConstantBuffer::createCbv(size_t handle, ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle) const
	{
		m_constantBufferDataArray.getMatchHandlePtr(handle)->createCbv(device, heapHandle);
	}

	ID3D12Resource* ConstantBuffer::getBufferPtr(size_t handle) const
	{
		return m_constantBufferDataArray.getMatchHandlePtr(handle)->getBufferPtr();
	}
}