#include "TktkDX12Wrapper/Resource/Buffer/Vertex/VertexBuffer.h"

namespace tktk
{
	VertexBuffer::VertexBuffer(const tktkContainer::ResourceContainerInitParam& initParam)
		: m_vertexBufferDataArray(initParam)
	{
	}

	unsigned int VertexBuffer::create(ID3D12Device* device, unsigned int vertexTypeSize, unsigned int vertexDataCount, const void* vertexDataTopPos)
	{
		return m_vertexBufferDataArray.create(device, vertexTypeSize, vertexDataCount, vertexDataTopPos);
	}

	void VertexBuffer::set(unsigned int handle, ID3D12GraphicsCommandList* commandList) const
	{
		m_vertexBufferDataArray.getMatchHandlePtr(handle)->set(commandList);
	}

	void VertexBuffer::updateBuffer(unsigned int handle, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, unsigned int vertexTypeSize, unsigned int vertexDataCount, const void* vertexDataTopPos)
	{
		m_vertexBufferDataArray.getMatchHandlePtr(handle)->updateBuffer(device, commandList, vertexTypeSize, vertexDataCount, vertexDataTopPos);
	}

	void VertexBuffer::deleteUploadBufferAll()
	{
		for (auto& node : m_vertexBufferDataArray)
		{
			node.deleteUploadBufferAll();
		}
	}
}