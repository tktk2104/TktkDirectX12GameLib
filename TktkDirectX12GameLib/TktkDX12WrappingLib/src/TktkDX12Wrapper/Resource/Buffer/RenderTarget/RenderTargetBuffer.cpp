#include "TktkDX12Wrapper/Resource/Buffer/RenderTarget/RenderTargetBuffer.h"

namespace tktk
{
	RenderTargetBuffer::RenderTargetBuffer(unsigned int renderTargetBufferNum)
		: m_renderTargetBufferDataArray(renderTargetBufferNum)
	{
	}

	void RenderTargetBuffer::create(unsigned int id, ID3D12Device* device, const tktkMath::Vector2& renderTargetSize, const tktkMath::Color& clearColor)
	{
		if (m_renderTargetBufferDataArray.at(id) != nullptr) m_renderTargetBufferDataArray.eraseAt(id);
		m_renderTargetBufferDataArray.emplaceAt(id, device, renderTargetSize, clearColor);
	}

	void RenderTargetBuffer::create(unsigned int id, IDXGISwapChain1* swapChain, unsigned int backBufferIndex)
	{
		if (m_renderTargetBufferDataArray.at(id) != nullptr) m_renderTargetBufferDataArray.eraseAt(id);
		m_renderTargetBufferDataArray.emplaceAt(id, swapChain, backBufferIndex);
	}

	void RenderTargetBuffer::beginWriteBasicRtBuffer(unsigned int id, ID3D12GraphicsCommandList* commandList) const
	{
		m_renderTargetBufferDataArray.at(id)->beginWriteBasicRtBuffer(commandList);
	}

	void RenderTargetBuffer::endWriteBasicRtBuffer(unsigned int id, ID3D12GraphicsCommandList* commandList) const
	{
		m_renderTargetBufferDataArray.at(id)->endWriteBasicRtBuffer(commandList);
	}

	void RenderTargetBuffer::beginWriteBackBuffer(unsigned int id, ID3D12GraphicsCommandList* commandList) const
	{
		m_renderTargetBufferDataArray.at(id)->beginWriteBackBuffer(commandList);
	}

	void RenderTargetBuffer::endWriteBackBuffer(unsigned int id, ID3D12GraphicsCommandList* commandList) const
	{
		m_renderTargetBufferDataArray.at(id)->endWriteBackBuffer(commandList);
	}

	void RenderTargetBuffer::createRtv(unsigned int id, ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle) const
	{
		m_renderTargetBufferDataArray.at(id)->createRtv(device, heapHandle);
	}

	void RenderTargetBuffer::createSrv(unsigned int id, ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle) const
	{
		m_renderTargetBufferDataArray.at(id)->createSrv(device, heapHandle);
	}

	const tktkMath::Vector2& RenderTargetBuffer::getRenderTargetSizePx(unsigned int id) const
	{
		return m_renderTargetBufferDataArray.at(id)->getRenderTargetSizePx();
	}
}