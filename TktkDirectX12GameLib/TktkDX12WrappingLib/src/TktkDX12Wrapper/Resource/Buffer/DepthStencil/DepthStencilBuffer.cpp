#include "TktkDX12Wrapper/Resource/Buffer/DepthStencil/DepthStencilBuffer.h"

namespace tktk
{
	DepthStencilBuffer::DepthStencilBuffer(const tktkContainer::ResourceContainerInitParam& initParam)
		: m_depthStencilBufferDataArray(initParam)
	{
	}

	size_t DepthStencilBuffer::create(ID3D12Device* device, const DepthStencilBufferInitParam& initParam)
	{
		return m_depthStencilBufferDataArray.create(device, initParam);
	}

	void DepthStencilBuffer::erase(size_t handle)
	{
		m_depthStencilBufferDataArray.erase(handle);
	}

	void DepthStencilBuffer::beginWrite(size_t handle, ID3D12GraphicsCommandList* commandList) const
	{
		m_depthStencilBufferDataArray.getMatchHandlePtr(handle)->beginWrite(commandList);
	}

	void DepthStencilBuffer::endWrite(size_t handle, ID3D12GraphicsCommandList* commandList) const
	{
		m_depthStencilBufferDataArray.getMatchHandlePtr(handle)->endWrite(commandList);
	}

	void DepthStencilBuffer::allBeginWrite(ID3D12GraphicsCommandList* commandList) const
	{
		for (const auto& node : m_depthStencilBufferDataArray)
		{
			node.beginWrite(commandList);
		}
	}

	void DepthStencilBuffer::allEndWrite(ID3D12GraphicsCommandList* commandList) const
	{
		for (const auto& node : m_depthStencilBufferDataArray)
		{
			node.endWrite(commandList);
		}
	}

	void DepthStencilBuffer::createDsv(size_t handle, ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle) const
	{
		m_depthStencilBufferDataArray.getMatchHandlePtr(handle)->createDsv(device, heapHandle);
	}

	void DepthStencilBuffer::createSrv(size_t handle, ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle) const
	{
		m_depthStencilBufferDataArray.getMatchHandlePtr(handle)->createSrv(device, heapHandle);
	}

	const tktkMath::Vector2& DepthStencilBuffer::getDepthStencilSizePx(size_t handle) const
	{
		return m_depthStencilBufferDataArray.getMatchHandlePtr(handle)->getDepthStencilSizePx();
	}

	ID3D12Resource* DepthStencilBuffer::getBufferPtr(size_t handle) const
	{
		return m_depthStencilBufferDataArray.getMatchHandlePtr(handle)->getBufferPtr();
	}
}