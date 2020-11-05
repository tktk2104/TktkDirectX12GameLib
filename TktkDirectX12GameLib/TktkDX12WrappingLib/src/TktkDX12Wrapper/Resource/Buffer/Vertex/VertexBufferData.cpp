#include "TktkDX12Wrapper/Resource/Buffer/Vertex/VertexBufferData.h"

#ifdef _DEBUG
#include <stdexcept>
#endif // _DEBUG

namespace tktk
{
	VertexBufferData::VertexBufferData(ID3D12Device* device, const VertexDataCarrier& vertexData)
	{
		D3D12_HEAP_PROPERTIES heapProp{};
		heapProp.Type					= D3D12_HEAP_TYPE_UPLOAD;
		heapProp.CPUPageProperty		= D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
		heapProp.MemoryPoolPreference	= D3D12_MEMORY_POOL_UNKNOWN;

		D3D12_RESOURCE_DESC resDesc{};
		resDesc.Dimension			= D3D12_RESOURCE_DIMENSION_BUFFER;
		resDesc.Format				= DXGI_FORMAT_UNKNOWN;
		resDesc.Width				= static_cast<UINT64>(vertexData.typeSize) * vertexData.dataCount;
		resDesc.Height				= 1;
		resDesc.DepthOrArraySize	= 1;
		resDesc.MipLevels			= 1;
		resDesc.SampleDesc.Count	= 1;
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

		{
			void* mappedVertexData{ nullptr };
			m_vertexBuffer->Map(0, nullptr, &mappedVertexData);
			memcpy(mappedVertexData, vertexData.dataTopPos, vertexData.typeSize * vertexData.dataCount);
			m_vertexBuffer->Unmap(0, nullptr);
		}

		m_vertexBufferView.BufferLocation	= m_vertexBuffer->GetGPUVirtualAddress();
		m_vertexBufferView.SizeInBytes		= static_cast<unsigned int>(vertexData.typeSize * vertexData.dataCount);
		m_vertexBufferView.StrideInBytes	= static_cast<unsigned int>(vertexData.typeSize);
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
}