#include "TktkDX12Wrapper/Resource/Buffer/DepthStencil/DepthStencilBuffer.h"

namespace tktk
{
	DepthStencilBuffer::DepthStencilBuffer(const tktkContainer::ResourceContainerInitParam& initParam)
		: m_depthStencilBufferDataArray(initParam)
	{
	}

	unsigned int DepthStencilBuffer::create(ID3D12Device* device, const DepthStencilBufferInitParam& initParam)
	{
		return m_depthStencilBufferDataArray.create(device, initParam);
	}

	void DepthStencilBuffer::erase(unsigned int handle)
	{
		m_depthStencilBufferDataArray.erase(handle);
	}

	void DepthStencilBuffer::beginWrite(unsigned int handle, ID3D12GraphicsCommandList* commandList) const
	{
		m_depthStencilBufferDataArray.getMatchHandlePtr(handle)->beginWrite(commandList);
	}

	void DepthStencilBuffer::endWrite(unsigned int handle, ID3D12GraphicsCommandList* commandList) const
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

	void DepthStencilBuffer::createDsv(unsigned int handle, ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle) const
	{
		m_depthStencilBufferDataArray.getMatchHandlePtr(handle)->createDsv(device, heapHandle);
	}

	void DepthStencilBuffer::createSrv(unsigned int handle, ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle) const
	{
		m_depthStencilBufferDataArray.getMatchHandlePtr(handle)->createSrv(device, heapHandle);
	}

	const tktkMath::Vector2& DepthStencilBuffer::getDepthStencilSizePx(unsigned int handle) const
	{
		return m_depthStencilBufferDataArray.getMatchHandlePtr(handle)->getDepthStencilSizePx();
	}
}