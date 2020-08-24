#include "TktkDX12Wrapper/Resource/Buffer/Index/IndexBuffer.h"

namespace tktk
{
	IndexBuffer::IndexBuffer(unsigned int indexBufferNum)
		: m_indexBufferDataArray(indexBufferNum)
	{
	}

	void IndexBuffer::create(unsigned int id, ID3D12Device* device, const std::vector<unsigned short>& indexDataArray)
	{
		if (m_indexBufferDataArray.at(id) != nullptr) m_indexBufferDataArray.eraseAt(id);
		m_indexBufferDataArray.emplaceAt(id, device, indexDataArray);
	}

	void IndexBuffer::set(unsigned int id, ID3D12GraphicsCommandList* commandList) const
	{
		m_indexBufferDataArray.at(id)->set(commandList);
	}

	void IndexBuffer::updateBuffer(unsigned int id, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, const std::vector<unsigned short>& indexDataArray)
	{
		m_indexBufferDataArray.at(id)->updateBuffer(device, commandList, indexDataArray);
	}

	void IndexBuffer::deleteUploadBufferAll()
	{
		for (auto& node : m_indexBufferDataArray)
		{
			node.deleteUploadBufferAll();
		}
	}
}