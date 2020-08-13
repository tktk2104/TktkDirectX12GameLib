#include "TktkDX12Wrapper/Resource/Buffer/Vertex/VertexBuffer.h"

namespace tktk
{
	VertexBuffer::VertexBuffer(unsigned int vertexBufferNum)
		: m_vertexBufferDataArray(vertexBufferNum)
	{
	}

	void VertexBuffer::create(unsigned int id, ID3D12Device* device, unsigned int vertexTypeSize, unsigned int vertexDataCount, const void* vertexDataTopPos)
	{
		if (m_vertexBufferDataArray.at(id) != nullptr) m_vertexBufferDataArray.eraseAt(id);
		m_vertexBufferDataArray.emplaceAt(id, device, vertexTypeSize, vertexDataCount, vertexDataTopPos);
	}

	void VertexBuffer::set(unsigned int id, ID3D12GraphicsCommandList* commandList) const
	{
		m_vertexBufferDataArray.at(id)->set(commandList);
	}

	void VertexBuffer::updateBuffer(unsigned int id, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, unsigned int vertexTypeSize, unsigned int vertexDataCount, const void* vertexDataTopPos)
	{
		m_vertexBufferDataArray.at(id)->updateBuffer(device, commandList, vertexTypeSize, vertexDataCount, vertexDataTopPos);
	}

	void VertexBuffer::deleteUploadBufferAll()
	{
		for (unsigned int i = 0; i < m_vertexBufferDataArray.arrayMaxSize(); i++)
		{
			auto ptr = m_vertexBufferDataArray.at(i);

			if (ptr != nullptr) ptr->deleteUploadBufferAll();
		}
	}
}