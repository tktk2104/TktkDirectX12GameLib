#include "TktkDX12Wrapper/Resource/Buffer/Vertex/VertexBufferData.h"

#ifdef _DEBUG
#include <stdexcept>
#endif // _DEBUG

namespace tktk
{
	VertexBufferData::VertexBufferData(ID3D12Device* device, size_t strideDataSize, size_t allDataSize)
	{
		D3D12_HEAP_PROPERTIES heapProp{};
		heapProp.Type					= D3D12_HEAP_TYPE_DEFAULT;
		heapProp.CPUPageProperty		= D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
		heapProp.MemoryPoolPreference	= D3D12_MEMORY_POOL_UNKNOWN;
		heapProp.CreationNodeMask		= 0U;
		heapProp.VisibleNodeMask		= 0U;

		D3D12_RESOURCE_DESC resDesc{};
		resDesc.Dimension			= D3D12_RESOURCE_DIMENSION_BUFFER;
		resDesc.Format				= DXGI_FORMAT_UNKNOWN;
		resDesc.Width				= static_cast<UINT64>((allDataSize + 0xff) & ~0xff);
		resDesc.Height				= 1;
		resDesc.DepthOrArraySize	= 1;
		resDesc.MipLevels			= 1;
		resDesc.SampleDesc.Count	= 1;
		resDesc.SampleDesc.Quality	= 0;
		resDesc.Flags				= D3D12_RESOURCE_FLAG_NONE;
		resDesc.Layout				= D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

		device->CreateCommittedResource(
			&heapProp,
			D3D12_HEAP_FLAG_NONE,
			&resDesc,
			D3D12_RESOURCE_STATE_GENERIC_READ,
			nullptr,
			IID_PPV_ARGS(&m_vertexBuffer)
		);

		m_vertexBufferView.BufferLocation	= m_vertexBuffer->GetGPUVirtualAddress();
		m_vertexBufferView.SizeInBytes		= static_cast<unsigned int>(allDataSize);
		m_vertexBufferView.StrideInBytes	= static_cast<unsigned int>(strideDataSize);
	}

	VertexBufferData::~VertexBufferData()
	{
		if (m_vertexBuffer != nullptr)
		{
			m_vertexBuffer->Release();
		}
	}

	VertexBufferData::VertexBufferData(VertexBufferData&& other) noexcept
		: m_vertexBuffer(other.m_vertexBuffer)
		, m_vertexBufferView(other.m_vertexBufferView)
	{
		m_vertexBuffer = nullptr;
	}

	void VertexBufferData::set(ID3D12GraphicsCommandList* commandList) const
	{
		commandList->IASetVertexBuffers(0, 1, &m_vertexBufferView);
	}

	ID3D12Resource* VertexBufferData::getBufferPtr() const
	{
		return m_vertexBuffer;
	}

	const D3D12_VERTEX_BUFFER_VIEW& VertexBufferData::getBufferView() const
	{
		return m_vertexBufferView;
	}
}