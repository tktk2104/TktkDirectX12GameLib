#include "TktkDX12Wrapper/Resource/Buffer/DepthStencil/DepthStencilBuffer.h"

namespace tktk
{
	DepthStencilBuffer::DepthStencilBuffer(unsigned int depthStencilBufferNum)
		: m_depthStencilBufferDataArray(depthStencilBufferNum)
	{
	}

	void DepthStencilBuffer::create(unsigned int id, ID3D12Device* device, const DepthStencilBufferInitParam& initParam)
	{
		if (m_depthStencilBufferDataArray.at(id) != nullptr) m_depthStencilBufferDataArray.eraseAt(id);
		m_depthStencilBufferDataArray.emplaceAt(id, device, initParam);
	}

	void DepthStencilBuffer::beginWrite(unsigned int id, ID3D12GraphicsCommandList* commandList) const
	{
		m_depthStencilBufferDataArray.at(id)->beginWrite(commandList);
	}

	void DepthStencilBuffer::endWrite(unsigned int id, ID3D12GraphicsCommandList* commandList) const
	{
		m_depthStencilBufferDataArray.at(id)->endWrite(commandList);
	}

	void DepthStencilBuffer::allBeginWrite(ID3D12GraphicsCommandList* commandList) const
	{
		for (unsigned int i = 0; i < m_depthStencilBufferDataArray.arrayMaxSize(); i++)
		{
			auto ptr = m_depthStencilBufferDataArray.at(i);

			if (ptr != nullptr) ptr->beginWrite(commandList);
		}
	}

	void DepthStencilBuffer::allEndWrite(ID3D12GraphicsCommandList* commandList) const
	{
		for (unsigned int i = 0; i < m_depthStencilBufferDataArray.arrayMaxSize(); i++)
		{
			auto ptr = m_depthStencilBufferDataArray.at(i);

			if (ptr != nullptr) ptr->endWrite(commandList);
		}
	}

	void DepthStencilBuffer::createDsv(unsigned int id, ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle) const
	{
		m_depthStencilBufferDataArray.at(id)->createDsv(device, heapHandle);
	}

	void DepthStencilBuffer::createSrv(unsigned int id, ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle) const
	{
		m_depthStencilBufferDataArray.at(id)->createSrv(device, heapHandle);
	}

	const tktkMath::Vector2& DepthStencilBuffer::getDepthStencilSizePx(unsigned int id) const
	{
		return m_depthStencilBufferDataArray.at(id)->getDepthStencilSizePx();
	}
}