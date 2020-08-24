#include "TktkDX12Wrapper/Resource/Buffer/Constant/ConstantBuffer.h"

namespace tktk
{
	ConstantBuffer::ConstantBuffer(unsigned int constantBufferNum)
		: m_constantBufferDataArray(constantBufferNum)
	{
	}

	void ConstantBuffer::create(unsigned int id, ID3D12Device* device, unsigned int constantBufferTypeSize, const void* constantBufferDataTopPos)
	{
		if (m_constantBufferDataArray.at(id) != nullptr) m_constantBufferDataArray.eraseAt(id);
		m_constantBufferDataArray.emplaceAt(id, device, constantBufferTypeSize, constantBufferDataTopPos);
	}

	void ConstantBuffer::createCbv(unsigned int id, ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle) const
	{
		m_constantBufferDataArray.at(id)->createCbv(device, heapHandle);
	}

	void ConstantBuffer::updateBuffer(unsigned int id, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, unsigned int constantBufferTypeSize, const void* constantBufferDataTopPos)
	{
		m_constantBufferDataArray.at(id)->updateBuffer(device, commandList, constantBufferTypeSize, constantBufferDataTopPos);
	}

	void ConstantBuffer::deleteUploadBufferAll()
	{
		for (auto& node : m_constantBufferDataArray)
		{
			node.deleteUploadBufferAll();
		}
	}
}