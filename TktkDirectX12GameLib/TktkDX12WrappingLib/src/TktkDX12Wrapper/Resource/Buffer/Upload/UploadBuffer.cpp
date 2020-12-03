#include "TktkDX12Wrapper/Resource/Buffer/Upload/UploadBuffer.h"

namespace tktk
{
	UploadBuffer::UploadBuffer(const tktkContainer::ResourceContainerInitParam& initParam)
		: m_uploadBufferDataArray(initParam)
	{
	}

	size_t UploadBuffer::create(ID3D12Device* device, const UploadBufferInitParam& initParam)
	{
		return m_uploadBufferDataArray.create(device, initParam);
	}

	size_t UploadBuffer::duplicate(ID3D12Device* device, size_t originalHandle)
	{
		return m_uploadBufferDataArray.create(device, *(m_uploadBufferDataArray.getMatchHandlePtr(originalHandle)));
	}

	void UploadBuffer::erase(size_t handle)
	{
		m_uploadBufferDataArray.erase(handle);
	}

	void UploadBuffer::updateBuffer(size_t handle, const CopySourceDataCarrier& bufferData)
	{
		m_uploadBufferDataArray.getMatchHandlePtr(handle)->updateBuffer(bufferData);
	}

	BufferType UploadBuffer::getTargetBufferType(size_t handle) const
	{
		return m_uploadBufferDataArray.getMatchHandlePtr(handle)->getTargetBufferType();
	}

	size_t UploadBuffer::getTargetBufferHandle(size_t handle) const
	{
		return m_uploadBufferDataArray.getMatchHandlePtr(handle)->getTargetBufferHandle();
	}

	void UploadBuffer::copyBuffer(size_t handle, ID3D12GraphicsCommandList* commandList, ID3D12Resource* targetBuffer) const
	{
		m_uploadBufferDataArray.getMatchHandlePtr(handle)->copyBuffer(commandList, targetBuffer);
	}

	void UploadBuffer::copyTexture(size_t handle, ID3D12GraphicsCommandList* commandList, ID3D12Resource* targetBuffer, const D3D12_TEXTURE_COPY_LOCATION& srcCopyLoaction) const
	{
		m_uploadBufferDataArray.getMatchHandlePtr(handle)->copyTexture(commandList, targetBuffer, srcCopyLoaction);
	}
}