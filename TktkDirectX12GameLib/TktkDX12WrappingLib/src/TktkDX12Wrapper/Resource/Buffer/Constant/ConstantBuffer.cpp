#include "TktkDX12Wrapper/Resource/Buffer/Constant/ConstantBuffer.h"

namespace tktk
{
	ConstantBuffer::ConstantBuffer(const tktkContainer::ResourceContainerInitParam& initParam)
		: m_constantBufferDataArray(initParam)
	{
	}

	unsigned int ConstantBuffer::create(ID3D12Device* device, unsigned int constantBufferTypeSize, const void* constantBufferDataTopPos)
	{
		return m_constantBufferDataArray.create(device, constantBufferTypeSize, constantBufferDataTopPos);
	}

	void ConstantBuffer::erase(unsigned int handle)
	{
		m_constantBufferDataArray.erase(handle);
	}

	void ConstantBuffer::createCbv(unsigned int handle, ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle) const
	{
		m_constantBufferDataArray.getMatchHandlePtr(handle)->createCbv(device, heapHandle);
	}

	ID3D12Resource* ConstantBuffer::getBufferPtr(unsigned int handle) const
	{
		return m_constantBufferDataArray.getMatchHandlePtr(handle)->getBufferPtr();
	}
}