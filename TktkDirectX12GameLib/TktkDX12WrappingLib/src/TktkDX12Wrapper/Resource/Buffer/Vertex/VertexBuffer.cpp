#include "TktkDX12Wrapper/Resource/Buffer/Vertex/VertexBuffer.h"

namespace tktk
{
	VertexBuffer::VertexBuffer(const tktkContainer::ResourceContainerInitParam& initParam)
		: m_vertexBufferDataArray(initParam)
	{
	}

	size_t VertexBuffer::create(ID3D12Device* device, const VertexDataCarrier& vertexData)
	{
		return m_vertexBufferDataArray.create(device, vertexData);
	}

	void VertexBuffer::erase(size_t handle)
	{
		m_vertexBufferDataArray.erase(handle);
	}

	void VertexBuffer::update(size_t handle, const VertexDataCarrier& vertexData)
	{
		m_vertexBufferDataArray.getMatchHandlePtr(handle)->update(vertexData);
	}

	void VertexBuffer::set(size_t handle, ID3D12GraphicsCommandList* commandList) const
	{
		m_vertexBufferDataArray.getMatchHandlePtr(handle)->set(commandList);
	}

	void VertexBuffer::set(size_t meshVertHandle, size_t instancingVertHandle, ID3D12GraphicsCommandList* commandList) const
	{
		const D3D12_VERTEX_BUFFER_VIEW tempBuf[2] = {
			m_vertexBufferDataArray.getMatchHandlePtr(meshVertHandle)->getBufferView(),
			m_vertexBufferDataArray.getMatchHandlePtr(instancingVertHandle)->getBufferView()
		};
		commandList->IASetVertexBuffers(0, 2, tempBuf);
	}

	ID3D12Resource* VertexBuffer::getBufferPtr(size_t handle) const
	{
		return m_vertexBufferDataArray.getMatchHandlePtr(handle)->getBufferPtr();
	}
}