#include "TktkDX12Wrapper/Resource/Buffer/Copy/CopyBuffer.h"

namespace tktk
{
	CopyBuffer::CopyBuffer(const tktkContainer::ResourceContainerInitParam& initParam)
		: m_copyBufferDataArray(initParam)
	{
	}

	unsigned int CopyBuffer::create(ID3D12Device* device, const CopyBufferInitParam& initParam)
	{
		return m_copyBufferDataArray.create(device, initParam);
	}

	unsigned int CopyBuffer::copy(ID3D12Device* device, unsigned int originalHandle)
	{
		return m_copyBufferDataArray.create(device, *(m_copyBufferDataArray.getMatchHandlePtr(originalHandle)));
	}

	void CopyBuffer::erase(unsigned int handle)
	{
		m_copyBufferDataArray.erase(handle);
	}

	void CopyBuffer::updateBuffer(unsigned int handle, unsigned int bufferSize, const void* bufferDataTopPos)
	{
		m_copyBufferDataArray.getMatchHandlePtr(handle)->updateBuffer(bufferSize, bufferDataTopPos);
	}

	BufferType CopyBuffer::getTargetBufferType(unsigned int handle) const
	{
		return m_copyBufferDataArray.getMatchHandlePtr(handle)->getTargetBufferType();
	}

	unsigned int CopyBuffer::getTargetBufferHandle(unsigned int handle) const
	{
		return m_copyBufferDataArray.getMatchHandlePtr(handle)->getTargetBufferHandle();
	}

	void CopyBuffer::copyBuffer(unsigned int handle, ID3D12GraphicsCommandList* commandList, ID3D12Resource* targetBuffer) const
	{
		m_copyBufferDataArray.getMatchHandlePtr(handle)->copyBuffer(commandList, targetBuffer);
	}
}