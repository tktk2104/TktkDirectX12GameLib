#include "TktkDX12Wrapper/Resource/Buffer/Constant/ConstantBufferData.h"

#include <algorithm>
#ifdef _DEBUG
#include <stdexcept>
#endif // _DEBUG

namespace tktk
{
	ConstantBufferData::ConstantBufferData(ID3D12Device* device, const CopySourceDataCarrier& constantBufferData)
	{
		// GPUアクセスに特化したヒープを作る（シェーダーが使用する）
		D3D12_HEAP_PROPERTIES constBuffHeapProp{};
		constBuffHeapProp.Type					= D3D12_HEAP_TYPE_DEFAULT;//D3D12_HEAP_TYPE_UPLOAD;
		constBuffHeapProp.CPUPageProperty		= D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
		constBuffHeapProp.MemoryPoolPreference	= D3D12_MEMORY_POOL_UNKNOWN;
		constBuffHeapProp.CreationNodeMask		= 0U;
		constBuffHeapProp.VisibleNodeMask		= 0U;

		D3D12_RESOURCE_DESC resDesc{};
		resDesc.Dimension			= D3D12_RESOURCE_DIMENSION_BUFFER;
		resDesc.Format				= DXGI_FORMAT_UNKNOWN;
		resDesc.Width				= static_cast<UINT64>((constantBufferData.dataSize + 0xff) & ~0xff);
		resDesc.Height				= 1;
		resDesc.DepthOrArraySize	= 1;
		resDesc.MipLevels			= 1;
		resDesc.SampleDesc.Count	= 1;
		resDesc.SampleDesc.Quality	= 0;
		resDesc.Flags				= D3D12_RESOURCE_FLAG_NONE;
		resDesc.Layout				= D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

		device->CreateCommittedResource(
			&constBuffHeapProp,
			D3D12_HEAP_FLAG_NONE,
			&resDesc,
			D3D12_RESOURCE_STATE_GENERIC_READ,
			nullptr,
			IID_PPV_ARGS(&m_constantBuffer)
		);
	}

	ConstantBufferData::~ConstantBufferData()
	{
		if (m_constantBuffer != nullptr)
		{
			m_constantBuffer->Release();
		}
	}

	ConstantBufferData::ConstantBufferData(ConstantBufferData&& other) noexcept
		: m_constantBuffer(other.m_constantBuffer)
	{
		other.m_constantBuffer = nullptr;
	}

	void ConstantBufferData::createCbv(ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle) const
	{
		D3D12_CONSTANT_BUFFER_VIEW_DESC cbvDesc{};
		cbvDesc.BufferLocation	= m_constantBuffer->GetGPUVirtualAddress();
		cbvDesc.SizeInBytes		= static_cast<UINT>(m_constantBuffer->GetDesc().Width);

		device->CreateConstantBufferView(&cbvDesc, heapHandle);
	}

	ID3D12Resource* ConstantBufferData::getBufferPtr() const
	{
		return m_constantBuffer;
	}
}