#include "TktkDX12Wrapper/Resource/Buffer/RenderTarget/RenderTargetBufferData.h"

namespace tktk
{
	RenderTargetBufferData::RenderTargetBufferData(ID3D12Device* device, const tktkMath::Vector2& renderTargetSize, const tktkMath::Color& clearColor)
		: m_renderTargetSize(renderTargetSize)
	{
		D3D12_RESOURCE_DESC resDesc{};
		resDesc.Dimension			= D3D12_RESOURCE_DIMENSION_TEXTURE2D;
		resDesc.Alignment			= 65536U;
		resDesc.Width				= static_cast<unsigned int>(renderTargetSize.x);
		resDesc.Height				= static_cast<unsigned int>(renderTargetSize.y);
		resDesc.DepthOrArraySize	= 1;
		resDesc.MipLevels			= 1;
		resDesc.Format				= DXGI_FORMAT_R8G8B8A8_UNORM;
		resDesc.SampleDesc.Count	= 1;
		resDesc.Flags				= D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET;

		D3D12_HEAP_PROPERTIES heapProp{};
		heapProp.Type					= D3D12_HEAP_TYPE_DEFAULT;
		heapProp.CPUPageProperty		= D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
		heapProp.MemoryPoolPreference	= D3D12_MEMORY_POOL_UNKNOWN;
		heapProp.CreationNodeMask		= 0U;
		heapProp.VisibleNodeMask		= 0U;

		D3D12_CLEAR_VALUE clearValue;
		clearValue.Color[0] = clearColor.r;
		clearValue.Color[1] = clearColor.g;
		clearValue.Color[2] = clearColor.b;
		clearValue.Color[3] = clearColor.a;
		clearValue.Format	= DXGI_FORMAT_R8G8B8A8_UNORM; //DXGI_FORMAT_R32G32B32A32_FLOAT;//

		device->CreateCommittedResource(
			&heapProp,
			D3D12_HEAP_FLAG_NONE,
			&resDesc,
			D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE, //D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE D3D12_RESOURCE_STATE_RENDER_TARGET
			&clearValue,
			IID_PPV_ARGS(&m_renderTargetBuffer)
		);
	}

	RenderTargetBufferData::RenderTargetBufferData(IDXGISwapChain1* swapChain, unsigned int backBufferIndex)
	{
		DXGI_SWAP_CHAIN_DESC1 desc{};
		swapChain->GetDesc1(&desc);

		m_renderTargetSize	= { static_cast<float>(desc.Width), static_cast<float>(desc.Height) };
		m_mustRelease		= false;
		swapChain->GetBuffer(backBufferIndex, IID_PPV_ARGS(&m_renderTargetBuffer));
	}

	RenderTargetBufferData::~RenderTargetBufferData()
	{
		if (m_mustRelease && m_renderTargetBuffer != nullptr)
		{
			m_renderTargetBuffer->Release();
		}
	}

	RenderTargetBufferData::RenderTargetBufferData(RenderTargetBufferData&& other) noexcept
		: m_mustRelease(other.m_mustRelease)
		, m_renderTargetSize(other.m_renderTargetSize)
		, m_renderTargetBuffer(other.m_renderTargetBuffer)
	{
		other.m_renderTargetBuffer = nullptr;
	}

	void RenderTargetBufferData::beginWriteBasicRtBuffer(ID3D12GraphicsCommandList* commandList) const
	{
		D3D12_RESOURCE_BARRIER barrierDesc{};
		barrierDesc.Type					= D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
		barrierDesc.Flags					= D3D12_RESOURCE_BARRIER_FLAG_NONE;
		barrierDesc.Transition.pResource	= m_renderTargetBuffer;
		barrierDesc.Transition.Subresource	= 0;
		barrierDesc.Transition.StateBefore	= D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE;
		barrierDesc.Transition.StateAfter	= D3D12_RESOURCE_STATE_RENDER_TARGET;

		commandList->ResourceBarrier(1, &barrierDesc);
	}

	void RenderTargetBufferData::endWriteBasicRtBuffer(ID3D12GraphicsCommandList* commandList) const
	{
		D3D12_RESOURCE_BARRIER barrierDesc{};
		barrierDesc.Type					= D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
		barrierDesc.Flags					= D3D12_RESOURCE_BARRIER_FLAG_NONE;
		barrierDesc.Transition.pResource	= m_renderTargetBuffer;
		barrierDesc.Transition.Subresource	= 0;
		barrierDesc.Transition.StateBefore	= D3D12_RESOURCE_STATE_RENDER_TARGET;
		barrierDesc.Transition.StateAfter	= D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE;

		commandList->ResourceBarrier(1, &barrierDesc);
	}

	void RenderTargetBufferData::beginWriteBackBuffer(ID3D12GraphicsCommandList* commandList) const
	{
		D3D12_RESOURCE_BARRIER barrierDesc{};
		barrierDesc.Type					= D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
		barrierDesc.Flags					= D3D12_RESOURCE_BARRIER_FLAG_NONE;
		barrierDesc.Transition.pResource	= m_renderTargetBuffer;
		barrierDesc.Transition.Subresource	= 0;
		barrierDesc.Transition.StateBefore	= D3D12_RESOURCE_STATE_PRESENT;
		barrierDesc.Transition.StateAfter	= D3D12_RESOURCE_STATE_RENDER_TARGET;

		commandList->ResourceBarrier(1, &barrierDesc);
	}

	void RenderTargetBufferData::endWriteBackBuffer(ID3D12GraphicsCommandList* commandList) const
	{
		D3D12_RESOURCE_BARRIER barrierDesc{};
		barrierDesc.Type					= D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
		barrierDesc.Flags					= D3D12_RESOURCE_BARRIER_FLAG_NONE;
		barrierDesc.Transition.pResource	= m_renderTargetBuffer;
		barrierDesc.Transition.Subresource	= 0;
		barrierDesc.Transition.StateBefore	= D3D12_RESOURCE_STATE_RENDER_TARGET;
		barrierDesc.Transition.StateAfter	= D3D12_RESOURCE_STATE_PRESENT;

		commandList->ResourceBarrier(1, &barrierDesc);
	}

	void RenderTargetBufferData::createRtv(ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle) const
	{
		D3D12_RENDER_TARGET_VIEW_DESC rtvDesc{};
		rtvDesc.ViewDimension	= D3D12_RTV_DIMENSION_TEXTURE2D;
		rtvDesc.Format			= DXGI_FORMAT_R8G8B8A8_UNORM;

		device->CreateRenderTargetView(m_renderTargetBuffer, &rtvDesc, heapHandle);
	}

	void RenderTargetBufferData::createSrv(ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle) const
	{
		D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{};
		srvDesc.ViewDimension			= D3D12_SRV_DIMENSION_TEXTURE2D;
		srvDesc.Format					= DXGI_FORMAT_R8G8B8A8_UNORM;
		srvDesc.Texture2D.MipLevels		= 1;
		srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;

		device->CreateShaderResourceView(m_renderTargetBuffer, &srvDesc, heapHandle);
	}

	const tktkMath::Vector2& RenderTargetBufferData::getRenderTargetSizePx() const
	{
		return m_renderTargetSize;
	}

	ID3D12Resource* RenderTargetBufferData::getBufferPtr() const
	{
		return m_renderTargetBuffer;
	}
}