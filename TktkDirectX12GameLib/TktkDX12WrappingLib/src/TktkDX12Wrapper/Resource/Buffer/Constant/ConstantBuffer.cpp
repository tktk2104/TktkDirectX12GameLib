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

	void ConstantBuffer::createCbv(unsigned int handle, ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle) const
	{
		m_constantBufferDataArray.getMatchHandlePtr(handle)->createCbv(device, heapHandle);
	}

	void ConstantBuffer::updateBuffer(unsigned int handle, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, unsigned int constantBufferTypeSize, const void* constantBufferDataTopPos)
	{
		m_constantBufferDataArray.getMatchHandlePtr(handle)->updateBuffer(device, commandList, constantBufferTypeSize, constantBufferDataTopPos);
	}

	void ConstantBuffer::deleteUploadBufferAll()
	{
		for (auto& node : m_constantBufferDataArray)
		{
			node.deleteUploadBufferAll();
		}
	}
}