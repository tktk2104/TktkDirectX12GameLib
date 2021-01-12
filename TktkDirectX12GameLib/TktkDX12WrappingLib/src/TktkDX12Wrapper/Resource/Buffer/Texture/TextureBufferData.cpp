#include "TktkDX12Wrapper/Resource/Buffer/Texture/TextureBufferData.h"

#include "TktkDX12Wrapper/Resource/Buffer/CopySourceDataCarrier.h"

namespace tktk
{
	TextureBufferData::TextureBufferData(ID3D12Device* device, const TexBufFormatParam& formatParam, const TexBuffData& dataParam)
	{
		m_textureSize = { static_cast<float>(dataParam.width), static_cast<float>(dataParam.height), static_cast<float>(dataParam.depth) };

		m_srvInitParam.format = formatParam.format;

		if (formatParam.arraySize > 1U)
		{
			switch (formatParam.resourceDimension)
			{
			case D3D12_RESOURCE_DIMENSION_TEXTURE1D:

				m_srvInitParam.viewDimension = D3D12_SRV_DIMENSION_TEXTURE1DARRAY;
				break;

			case D3D12_RESOURCE_DIMENSION_TEXTURE2D:

				// TODO : CubeMapの場合の条件式を作る
				m_srvInitParam.viewDimension = D3D12_SRV_DIMENSION_TEXTURE2DARRAY;
				break;
			}
		}
		else
		{
			switch (formatParam.resourceDimension)
			{
			case D3D12_RESOURCE_DIMENSION_TEXTURE1D:

				m_srvInitParam.viewDimension = D3D12_SRV_DIMENSION_TEXTURE1D;
				break;

			case D3D12_RESOURCE_DIMENSION_TEXTURE2D:

				// TODO : CubeMapの場合の条件式を作る
				m_srvInitParam.viewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
				break;

			case D3D12_RESOURCE_DIMENSION_TEXTURE3D:

				m_srvInitParam.viewDimension = D3D12_SRV_DIMENSION_TEXTURE3D;
				break;
			}
		}

		m_srvInitParam.mostDetailedMip = 0;
		m_srvInitParam.mipLevels = formatParam.mipLevels;
		m_srvInitParam.firstArraySlice = 0;
		m_srvInitParam.arraySize = formatParam.arraySize;
		m_srvInitParam.planeSlice = 0;
		m_srvInitParam.minLodClamp = 0.0f;

		D3D12_HEAP_PROPERTIES texHeapProp{};
		texHeapProp.Type = D3D12_HEAP_TYPE_DEFAULT;
		texHeapProp.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
		texHeapProp.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
		texHeapProp.CreationNodeMask = 0;
		texHeapProp.VisibleNodeMask = 0;

		// シェーダーが使用するバッファなのでちゃんとテクスチャとして解釈させる
		D3D12_RESOURCE_DESC resDesc{};
		resDesc.Dimension = formatParam.resourceDimension;
		resDesc.Format = formatParam.format;
		resDesc.Width = dataParam.width;
		resDesc.Height = dataParam.height;
		resDesc.DepthOrArraySize = (dataParam.depth > 1U) ? dataParam.depth : formatParam.arraySize;
		resDesc.MipLevels = formatParam.mipLevels;
		resDesc.SampleDesc.Count = formatParam.sampleDescCount;
		resDesc.SampleDesc.Quality = formatParam.sampleDescQuality;
		resDesc.Flags = D3D12_RESOURCE_FLAG_NONE;
		resDesc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;

		device->CreateCommittedResource(
			&texHeapProp,
			D3D12_HEAP_FLAG_NONE,
			&resDesc,
			D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE,
			nullptr,
			IID_PPV_ARGS(&m_textureBuffer)
		);
	}

	TextureBufferData::~TextureBufferData()
	{
		if (m_textureBuffer != nullptr)
		{
			m_textureBuffer->Release();
		}
	}

	TextureBufferData::TextureBufferData(TextureBufferData&& other) noexcept
		: m_textureSize(other.m_textureSize)
		, m_srvInitParam(other.m_srvInitParam)
		, m_textureBuffer(other.m_textureBuffer)
	{
		other.m_textureBuffer = nullptr;
	}

	void TextureBufferData::createSrv(ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle) const
	{
		D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{};
		srvDesc.Format = m_srvInitParam.format;
		srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
		srvDesc.ViewDimension = m_srvInitParam.viewDimension;

		switch (srvDesc.ViewDimension)
		{
		case D3D12_SRV_DIMENSION_TEXTURE1D:

			srvDesc.Texture1D.MipLevels				= m_srvInitParam.mipLevels;
			srvDesc.Texture1D.MostDetailedMip		= m_srvInitParam.mostDetailedMip;
			srvDesc.Texture1D.ResourceMinLODClamp	= m_srvInitParam.minLodClamp;
			break;

		case D3D12_SRV_DIMENSION_TEXTURE1DARRAY:

			srvDesc.Texture1DArray.MipLevels			= m_srvInitParam.mipLevels;
			srvDesc.Texture1DArray.MostDetailedMip		= m_srvInitParam.mostDetailedMip;
			srvDesc.Texture1DArray.FirstArraySlice		= m_srvInitParam.firstArraySlice;
			srvDesc.Texture1DArray.ArraySize			= m_srvInitParam.arraySize;
			srvDesc.Texture1DArray.ResourceMinLODClamp	= m_srvInitParam.minLodClamp;
			break;

		case D3D12_SRV_DIMENSION_TEXTURE2D:

			srvDesc.Texture2D.MipLevels				= m_srvInitParam.mipLevels;
			srvDesc.Texture2D.MostDetailedMip		= m_srvInitParam.mostDetailedMip;
			srvDesc.Texture2D.PlaneSlice			= m_srvInitParam.planeSlice;
			srvDesc.Texture2D.ResourceMinLODClamp	= m_srvInitParam.minLodClamp;
			break;

		case D3D12_SRV_DIMENSION_TEXTURE2DARRAY:

			srvDesc.Texture2DArray.MipLevels			= m_srvInitParam.mipLevels;
			srvDesc.Texture2DArray.MostDetailedMip		= m_srvInitParam.mostDetailedMip;
			srvDesc.Texture2DArray.FirstArraySlice		= m_srvInitParam.firstArraySlice;
			srvDesc.Texture2DArray.ArraySize			= m_srvInitParam.arraySize;
			srvDesc.Texture2DArray.PlaneSlice			= m_srvInitParam.planeSlice;
			srvDesc.Texture2DArray.ResourceMinLODClamp	= m_srvInitParam.minLodClamp;
			break;

		case D3D12_SRV_DIMENSION_TEXTURE3D:

			srvDesc.Texture3D.MipLevels				= m_srvInitParam.mipLevels;
			srvDesc.Texture3D.MostDetailedMip		= m_srvInitParam.mostDetailedMip;
			srvDesc.Texture3D.ResourceMinLODClamp	= m_srvInitParam.minLodClamp;
			break;

		case D3D12_SRV_DIMENSION_TEXTURECUBE:

			srvDesc.TextureCube.MipLevels			= m_srvInitParam.mipLevels;
			srvDesc.TextureCube.MostDetailedMip		= m_srvInitParam.mostDetailedMip;
			srvDesc.TextureCube.ResourceMinLODClamp = m_srvInitParam.minLodClamp;
			break;

		case D3D12_SRV_DIMENSION_TEXTURECUBEARRAY:

			srvDesc.TextureCubeArray.MipLevels				= m_srvInitParam.mipLevels;
			srvDesc.TextureCubeArray.MostDetailedMip		= m_srvInitParam.mostDetailedMip;
			srvDesc.TextureCubeArray.First2DArrayFace		= m_srvInitParam.firstArraySlice;
			srvDesc.TextureCubeArray.NumCubes				= m_srvInitParam.arraySize;
			srvDesc.TextureCubeArray.ResourceMinLODClamp	= m_srvInitParam.minLodClamp;
			break;
		}
		device->CreateShaderResourceView(m_textureBuffer, &srvDesc, heapHandle);
	}

	const tktkMath::Vector3& TextureBufferData::getTextureSizePx() const
	{
		return m_textureSize;
	}

	ID3D12Resource* TextureBufferData::getBufferPtr() const
	{
		return m_textureBuffer;
	}

	size_t TextureBufferData::getPixDataSizeByte() const
	{
		switch (m_srvInitParam.format)
		{
		case DXGI_FORMAT_R32G32B32A32_TYPELESS:
		case DXGI_FORMAT_R32G32B32A32_FLOAT:
		case DXGI_FORMAT_R32G32B32A32_UINT:
		case DXGI_FORMAT_R32G32B32A32_SINT:
			return 16U;
		case DXGI_FORMAT_R8G8B8A8_TYPELESS:
		case DXGI_FORMAT_R8G8B8A8_UNORM:
		case DXGI_FORMAT_R8G8B8A8_UNORM_SRGB:
		case DXGI_FORMAT_R8G8B8A8_UINT:
		case DXGI_FORMAT_R8G8B8A8_SNORM:
		case DXGI_FORMAT_R8G8B8A8_SINT:
			return 4U;
		}

		return 32U;
	}

	D3D12_TEXTURE_COPY_LOCATION TextureBufferData::createSrcCopyLoaction() const
	{
		D3D12_TEXTURE_COPY_LOCATION src{};
		src.pResource							= nullptr;
		src.Type								= D3D12_TEXTURE_COPY_TYPE_PLACED_FOOTPRINT;
		src.PlacedFootprint.Offset				= 0;
		src.PlacedFootprint.Footprint.Width		= static_cast<unsigned int>(m_textureSize.x);
		src.PlacedFootprint.Footprint.Height	= static_cast<unsigned int>(m_textureSize.y);
		src.PlacedFootprint.Footprint.Depth		= 1U;
		src.PlacedFootprint.Footprint.RowPitch	= ((static_cast<unsigned int>(m_textureSize.x) * getPixDataSizeByte()) + 0xff) & ~0xff;
		src.PlacedFootprint.Footprint.Format	= m_srvInitParam.format;

		return src;
	}
}