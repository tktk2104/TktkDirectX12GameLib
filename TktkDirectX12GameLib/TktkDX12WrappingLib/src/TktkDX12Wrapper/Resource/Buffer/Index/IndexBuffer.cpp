#include "TktkDX12Wrapper/Resource/Buffer/Index/IndexBuffer.h"

namespace tktk
{
	IndexBuffer::IndexBuffer(const tktkContainer::ResourceContainerInitParam& initParam)
		: m_indexBufferDataArray(initParam)
	{
	}

	unsigned int IndexBuffer::create(ID3D12Device* device, const std::vector<unsigned short>& indexDataArray)
	{
		return m_indexBufferDataArray.create(device, indexDataArray);
	}

	void IndexBuffer::erase(unsigned int handle)
	{
		m_indexBufferDataArray.erase(handle);
	}

	void IndexBuffer::set(unsigned int handle, ID3D12GraphicsCommandList* commandList) const
	{
		m_indexBufferDataArray.getMatchHandlePtr(handle)->set(commandList);
	}

	ID3D12Resource* IndexBuffer::getBufferPtr(unsigned int handle) const
	{
		return m_indexBufferDataArray.getMatchHandlePtr(handle)->getBufferPtr();
	}
}