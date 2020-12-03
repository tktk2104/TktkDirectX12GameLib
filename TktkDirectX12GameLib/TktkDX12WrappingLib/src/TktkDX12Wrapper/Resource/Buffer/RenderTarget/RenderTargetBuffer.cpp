#include "TktkDX12Wrapper/Resource/Buffer/RenderTarget/RenderTargetBuffer.h"

namespace tktk
{
	RenderTargetBuffer::RenderTargetBuffer(const tktkContainer::ResourceContainerInitParam& initParam)
		: m_renderTargetBufferDataArray(initParam)
	{
	}

	size_t RenderTargetBuffer::create(ID3D12Device* device, const tktkMath::Vector2& renderTargetSize, const tktkMath::Color& clearColor)
	{
		return m_renderTargetBufferDataArray.create(device, renderTargetSize, clearColor);
	}

	size_t RenderTargetBuffer::create(IDXGISwapChain1* swapChain, unsigned int backBufferIndex)
	{
		return m_renderTargetBufferDataArray.create(swapChain, backBufferIndex);
	}

	void RenderTargetBuffer::erase(size_t handle)
	{
		m_renderTargetBufferDataArray.erase(handle);
	}

	const tktkMath::Color& RenderTargetBuffer::getClearColor(size_t handle) const
	{
		return m_renderTargetBufferDataArray.getMatchHandlePtr(handle)->getClearColor();
	}

	void RenderTargetBuffer::beginWriteBasicRtBuffer(size_t handle, ID3D12GraphicsCommandList* commandList) const
	{
		m_renderTargetBufferDataArray.getMatchHandlePtr(handle)->beginWriteBasicRtBuffer(commandList);
	}

	void RenderTargetBuffer::endWriteBasicRtBuffer(size_t handle, ID3D12GraphicsCommandList* commandList) const
	{
		m_renderTargetBufferDataArray.getMatchHandlePtr(handle)->endWriteBasicRtBuffer(commandList);
	}

	void RenderTargetBuffer::beginWriteBackBuffer(size_t handle, ID3D12GraphicsCommandList* commandList) const
	{
		m_renderTargetBufferDataArray.getMatchHandlePtr(handle)->beginWriteBackBuffer(commandList);
	}

	void RenderTargetBuffer::endWriteBackBuffer(size_t handle, ID3D12GraphicsCommandList* commandList) const
	{
		m_renderTargetBufferDataArray.getMatchHandlePtr(handle)->endWriteBackBuffer(commandList);
	}

	void RenderTargetBuffer::createRtv(size_t handle, ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle) const
	{
		m_renderTargetBufferDataArray.getMatchHandlePtr(handle)->createRtv(device, heapHandle);
	}

	void RenderTargetBuffer::createSrv(size_t handle, ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle) const
	{
		m_renderTargetBufferDataArray.getMatchHandlePtr(handle)->createSrv(device, heapHandle);
	}

	const tktkMath::Vector2& RenderTargetBuffer::getRenderTargetSizePx(size_t handle) const
	{
		return m_renderTargetBufferDataArray.getMatchHandlePtr(handle)->getRenderTargetSizePx();
	}

	ID3D12Resource* RenderTargetBuffer::getBufferPtr(size_t handle) const
	{
		return m_renderTargetBufferDataArray.getMatchHandlePtr(handle)->getBufferPtr();
	}
}