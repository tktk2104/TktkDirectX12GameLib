#include "TktkDX12Wrapper/Resource/Buffer/DepthStencil/DepthStencilBufferData.h"

namespace tktk
{
	DepthStencilBufferData::DepthStencilBufferData(ID3D12Device* device, const DepthStencilBufferInitParam& initParam)
		: m_useAsShaderResource(initParam.useAsShaderResource)
		, m_depthStencilSize(initParam.depthStencilSize)
	{
		D3D12_RESOURCE_DESC depthStencilResDesc{};
		depthStencilResDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
		depthStencilResDesc.Width = static_cast<unsigned int>(initParam.depthStencilSize.x);
		depthStencilResDesc.Height = static_cast<unsigned int>(initParam.depthStencilSize.y);
		depthStencilResDesc.DepthOrArraySize = 1;
		depthStencilResDesc.MipLevels = 0;
		depthStencilResDesc.Format = (m_useAsShaderResource) ? DXGI_FORMAT_R32_TYPELESS : DXGI_FORMAT_D32_FLOAT;
		depthStencilResDesc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
		depthStencilResDesc.SampleDesc.Count = 1;
		depthStencilResDesc.SampleDesc.Quality = 0;
		depthStencilResDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;

		D3D12_HEAP_PROPERTIES depthHeapProp{};
		depthHeapProp.Type = D3D12_HEAP_TYPE_DEFAULT;
		depthHeapProp.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
		depthHeapProp.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
		depthHeapProp.CreationNodeMask	= 0; // ADD
		depthHeapProp.VisibleNodeMask	= 0; // ADD

		D3D12_CLEAR_VALUE depthClearValue{};
		depthClearValue.DepthStencil.Depth = 1.0f;
		depthClearValue.DepthStencil.Stencil = 0;
		depthClearValue.Format = DXGI_FORMAT_D32_FLOAT;

		device->CreateCommittedResource(
			&depthHeapProp,
			D3D12_HEAP_FLAG_NONE,
			&depthStencilResDesc,
			(m_useAsShaderResource) ? D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE : D3D12_RESOURCE_STATE_DEPTH_WRITE,
			&depthClearValue,
			IID_PPV_ARGS(&m_depthStencilBuffer)
		);
	}

	DepthStencilBufferData::~DepthStencilBufferData()
	{
		if (m_depthStencilBuffer != nullptr)
		{
			m_depthStencilBuffer->Release();
		}
	}

	DepthStencilBufferData::DepthStencilBufferData(DepthStencilBufferData&& other) noexcept
		: m_useAsShaderResource(std::move(other.m_useAsShaderResource))
		, m_depthStencilSize(std::move(other.m_depthStencilSize))
		, m_depthStencilBuffer(std::move(other.m_depthStencilBuffer))
	{
		m_depthStencilBuffer = nullptr;
	}

	void DepthStencilBufferData::beginWrite(ID3D12GraphicsCommandList* commandList) const
	{
		if (!m_useAsShaderResource) return;

		D3D12_RESOURCE_BARRIER barrierDesc{};
		barrierDesc.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
		barrierDesc.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
		barrierDesc.Transition.pResource = m_depthStencilBuffer;
		barrierDesc.Transition.Subresource = 0;
		barrierDesc.Transition.StateBefore = D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE;
		barrierDesc.Transition.StateAfter = D3D12_RESOURCE_STATE_DEPTH_WRITE;
		commandList->ResourceBarrier(1, &barrierDesc);
	}

	void DepthStencilBufferData::endWrite(ID3D12GraphicsCommandList* commandList) const
	{
		if (!m_useAsShaderResource) return;

		D3D12_RESOURCE_BARRIER barrierDesc{};
		barrierDesc.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
		barrierDesc.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
		barrierDesc.Transition.pResource = m_depthStencilBuffer;
		barrierDesc.Transition.Subresource = 0;
		barrierDesc.Transition.StateBefore = D3D12_RESOURCE_STATE_DEPTH_WRITE;
		barrierDesc.Transition.StateAfter = D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE;
		commandList->ResourceBarrier(1, &barrierDesc);
	}

	void DepthStencilBufferData::createDsv(ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle) const
	{
		D3D12_DEPTH_STENCIL_VIEW_DESC dsvDesc{};
		dsvDesc.Format = DXGI_FORMAT_D32_FLOAT;
		dsvDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
		dsvDesc.Texture2D.MipSlice = 0;
		dsvDesc.Flags = D3D12_DSV_FLAG_NONE;

		device->CreateDepthStencilView(
			m_depthStencilBuffer,
			&dsvDesc,
			heapHandle
		);
	}

	void DepthStencilBufferData::createSrv(ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle) const
	{
		D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{};
		srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
		srvDesc.Format = DXGI_FORMAT_R32_FLOAT;
		srvDesc.Texture2D.MipLevels = 1;
		srvDesc.Texture2D.MostDetailedMip = 0;
		srvDesc.Texture2D.PlaneSlice = 0;
		srvDesc.Texture2D.ResourceMinLODClamp = 0.0f;
		srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;

		device->CreateShaderResourceView(m_depthStencilBuffer, &srvDesc, heapHandle);
	}

	const tktkMath::Vector2& DepthStencilBufferData::getDepthStencilSizePx() const
	{
		return m_depthStencilSize;
	}
}