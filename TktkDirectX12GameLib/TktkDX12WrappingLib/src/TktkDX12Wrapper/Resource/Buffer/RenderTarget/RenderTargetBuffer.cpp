#include "TktkDX12Wrapper/Resource/Buffer/RenderTarget/RenderTargetBuffer.h"

namespace tktk
{
	RenderTargetBuffer::RenderTargetBuffer(const tktkContainer::ResourceContainerInitParam& initParam)
		: m_renderTargetBufferDataArray(initParam)
	{
	}

	unsigned int RenderTargetBuffer::create(ID3D12Device* device, const tktkMath::Vector2& renderTargetSize, const tktkMath::Color& clearColor)
	{
		return m_renderTargetBufferDataArray.create(device, renderTargetSize, clearColor);
	}

	unsigned int RenderTargetBuffer::create(IDXGISwapChain1* swapChain, unsigned int backBufferIndex)
	{
		return m_renderTargetBufferDataArray.create(swapChain, backBufferIndex);
	}

	void RenderTargetBuffer::erase(unsigned int handle)
	{
		m_renderTargetBufferDataArray.erase(handle);
	}

	void RenderTargetBuffer::beginWriteBasicRtBuffer(unsigned int handle, ID3D12GraphicsCommandList* commandList) const
	{
		m_renderTargetBufferDataArray.getMatchHandlePtr(handle)->beginWriteBasicRtBuffer(commandList);
	}

	void RenderTargetBuffer::endWriteBasicRtBuffer(unsigned int handle, ID3D12GraphicsCommandList* commandList) const
	{
		m_renderTargetBufferDataArray.getMatchHandlePtr(handle)->endWriteBasicRtBuffer(commandList);
	}

	void RenderTargetBuffer::beginWriteBackBuffer(unsigned int handle, ID3D12GraphicsCommandList* commandList) const
	{
		m_renderTargetBufferDataArray.getMatchHandlePtr(handle)->beginWriteBackBuffer(commandList);
	}

	void RenderTargetBuffer::endWriteBackBuffer(unsigned int handle, ID3D12GraphicsCommandList* commandList) const
	{
		m_renderTargetBufferDataArray.getMatchHandlePtr(handle)->endWriteBackBuffer(commandList);
	}

	void RenderTargetBuffer::createRtv(unsigned int handle, ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle) const
	{
		m_renderTargetBufferDataArray.getMatchHandlePtr(handle)->createRtv(device, heapHandle);
	}

	void RenderTargetBuffer::createSrv(unsigned int handle, ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle) const
	{
		m_renderTargetBufferDataArray.getMatchHandlePtr(handle)->createSrv(device, heapHandle);
	}

	const tktkMath::Vector2& RenderTargetBuffer::getRenderTargetSizePx(unsigned int handle) const
	{
		return m_renderTargetBufferDataArray.getMatchHandlePtr(handle)->getRenderTargetSizePx();
	}
}