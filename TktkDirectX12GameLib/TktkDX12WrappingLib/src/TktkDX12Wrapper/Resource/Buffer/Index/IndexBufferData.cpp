#include "TktkDX12Wrapper/Resource/Buffer/Index/IndexBufferData.h"

#ifdef _DEBUG
#include <stdexcept>
#endif // _DEBUG

namespace tktk
{
	IndexBufferData::IndexBufferData(ID3D12Device* device, size_t dataSize)
	{
		D3D12_HEAP_PROPERTIES heapProp{};
		heapProp.Type					= D3D12_HEAP_TYPE_DEFAULT;
		heapProp.CPUPageProperty		= D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
		heapProp.MemoryPoolPreference	= D3D12_MEMORY_POOL_UNKNOWN;

		D3D12_RESOURCE_DESC resDesc{};
		resDesc.Dimension			= D3D12_RESOURCE_DIMENSION_BUFFER;
		resDesc.Format				= DXGI_FORMAT_UNKNOWN;
		resDesc.Width				= static_cast<UINT64>((dataSize + 0xff) & ~0xff);
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
			IID_PPV_ARGS(&m_indexBuffer)
		);

		m_indexBufferView.BufferLocation	= m_indexBuffer->GetGPUVirtualAddress();
		m_indexBufferView.Format			= DXGI_FORMAT_R16_UINT;

		m_indexBufferView.SizeInBytes = static_cast<unsigned int>(dataSize);
	}

	IndexBufferData::~IndexBufferData()
	{
		if (m_indexBuffer != nullptr)
		{
			m_indexBuffer->Release();
		}
	}

	IndexBufferData::IndexBufferData(IndexBufferData&& other) noexcept
		: m_indexBuffer(other.m_indexBuffer)
		, m_indexBufferView(other.m_indexBufferView)
	{
		other.m_indexBuffer = nullptr;
	}

	void IndexBufferData::set(ID3D12GraphicsCommandList* commandList) const
	{
		commandList->IASetIndexBuffer(&m_indexBufferView);
	}

	ID3D12Resource* IndexBufferData::getBufferPtr() const
	{
		return m_indexBuffer;
	}
}