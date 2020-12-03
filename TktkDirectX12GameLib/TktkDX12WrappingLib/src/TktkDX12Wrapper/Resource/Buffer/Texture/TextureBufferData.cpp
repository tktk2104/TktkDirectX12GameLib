#include "TktkDX12Wrapper/Resource/Buffer/Texture/TextureBufferData.h"

namespace tktk
{
	TextureBufferData::TextureBufferData(ID3D12Device* device, const TexBufFormatParam& formatParam, const TexBuffData& dataParam)
	{
		// テクスチャサイズを保存する
		m_textureSize = { static_cast<float>(dataParam.width), static_cast<float>(dataParam.height), static_cast<float>(dataParam.depth) };

		{
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
		}


		D3D12_HEAP_PROPERTIES heapProp{};
		heapProp.Type					= D3D12_HEAP_TYPE_CUSTOM;
		heapProp.CPUPageProperty		= D3D12_CPU_PAGE_PROPERTY_WRITE_BACK;
		heapProp.MemoryPoolPreference	= D3D12_MEMORY_POOL_L0;
		heapProp.CreationNodeMask		= 0;
		heapProp.VisibleNodeMask		= 0;

		D3D12_RESOURCE_DESC resDesc{};
		resDesc.Dimension			= formatParam.resourceDimension;
		resDesc.Format				= formatParam.format;
		resDesc.Width				= dataParam.width;
		resDesc.Height				= dataParam.height;
		resDesc.DepthOrArraySize	= (dataParam.depth > 1U) ? dataParam.depth : formatParam.arraySize;
		resDesc.SampleDesc.Count	= formatParam.sampleDescCount;
		resDesc.SampleDesc.Quality	= formatParam.sampleDescQuality;
		resDesc.MipLevels			= formatParam.mipLevels;
		resDesc.Flags				= D3D12_RESOURCE_FLAG_NONE;
		resDesc.Layout				= D3D12_TEXTURE_LAYOUT_UNKNOWN;

		device->CreateCommittedResource(
			&heapProp,
			D3D12_HEAP_FLAG_NONE,
			&resDesc,
			D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE,
			nullptr,
			IID_PPV_ARGS(&m_textureBuffer)
		);

		m_textureBuffer->WriteToSubresource(
			0,
			nullptr,
			dataParam.textureData.data(),
			dataParam.width * 4,
#ifdef _M_AMD64 /* x64ビルドなら */
			static_cast<unsigned int>(dataParam.textureData.size())
#else
			dataParam.textureData.size()
#endif // WIN64
		);
	}

	TextureBufferData::TextureBufferData(ID3D12Device* device, ID3D12GraphicsCommandList* commandList, const TexBufFormatParam& formatParam, const TexBuffData& dataParam)
	{
		m_textureSize = { static_cast<float>(dataParam.width), static_cast<float>(dataParam.height), static_cast<float>(dataParam.depth) };

		{
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
			m_srvInitParam.mostDetailedMip	= 0;
			m_srvInitParam.mipLevels		= formatParam.mipLevels;
			m_srvInitParam.firstArraySlice	= 0;
			m_srvInitParam.arraySize		= formatParam.arraySize;
			m_srvInitParam.planeSlice		= 0;
			m_srvInitParam.minLodClamp		= 0.0f;
		}

		// CPUアクセスに特化したヒープを作る（CPUからテクスチャデータをコピーする時に使用する）
		{
			D3D12_HEAP_PROPERTIES uploadHeapProp{};
			uploadHeapProp.Type					= D3D12_HEAP_TYPE_UPLOAD;
			uploadHeapProp.CPUPageProperty		= D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
			uploadHeapProp.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
			uploadHeapProp.CreationNodeMask		= 0;
			uploadHeapProp.VisibleNodeMask		= 0;

			// 中間バッファなのでバッファはただのバイナリデータの塊として解釈させる
			D3D12_RESOURCE_DESC resDesc{};
			resDesc.Dimension			= D3D12_RESOURCE_DIMENSION_BUFFER;
			resDesc.Format				= DXGI_FORMAT_UNKNOWN;
			resDesc.Width				= ((dataParam.textureData.size()) + 0xff) & ~0xff;
			resDesc.Height				= 1;
			resDesc.DepthOrArraySize	= 1;
			resDesc.MipLevels			= 1;
			resDesc.SampleDesc.Count	= 1;
			resDesc.SampleDesc.Quality	= 0;
			resDesc.Flags				= D3D12_RESOURCE_FLAG_NONE;
			resDesc.Layout				= D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

			device->CreateCommittedResource(
				&uploadHeapProp,
				D3D12_HEAP_FLAG_NONE,
				&resDesc,
				D3D12_RESOURCE_STATE_GENERIC_READ,
				nullptr,
				IID_PPV_ARGS(&m_uploadBuff)
			);

			// テクスチャをCPUアクセス特化ヒープにコピーする
			unsigned char* mapForImg{ nullptr };
			m_uploadBuff->Map(0, nullptr, (void**)&mapForImg);
			std::copy_n(dataParam.textureData.data(), dataParam.textureData.size(), mapForImg);
			m_uploadBuff->Unmap(0, nullptr);
		}

		// GPUアクセスに特化したヒープを作る（シェーダーが使用する）
		{
			D3D12_HEAP_PROPERTIES texHeapProp{};
			texHeapProp.Type					= D3D12_HEAP_TYPE_DEFAULT;
			texHeapProp.CPUPageProperty			= D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
			texHeapProp.MemoryPoolPreference	= D3D12_MEMORY_POOL_UNKNOWN;
			texHeapProp.CreationNodeMask		= 0;
			texHeapProp.VisibleNodeMask			= 0;

			// シェーダーが使用するバッファなのでちゃんとテクスチャとして解釈させる
			D3D12_RESOURCE_DESC resDesc{};
			resDesc.Dimension			= formatParam.resourceDimension;
			resDesc.Format				= formatParam.format;
			resDesc.Width				= dataParam.width;
			resDesc.Height				= dataParam.height;
			resDesc.DepthOrArraySize	= (dataParam.depth > 1U) ? dataParam.depth : formatParam.arraySize;
			resDesc.MipLevels			= formatParam.mipLevels;
			resDesc.SampleDesc.Count	= formatParam.sampleDescCount;
			resDesc.SampleDesc.Quality	= formatParam.sampleDescQuality;
			resDesc.Flags				= D3D12_RESOURCE_FLAG_NONE;
			resDesc.Layout				= D3D12_TEXTURE_LAYOUT_UNKNOWN;

			device->CreateCommittedResource(
				&texHeapProp,
				D3D12_HEAP_FLAG_NONE,
				&resDesc,
				D3D12_RESOURCE_STATE_COPY_DEST,
				nullptr,
				IID_PPV_ARGS(&m_textureBuffer)
			);
		}

		unsigned int pixDataSizeByte = 0U;

		switch (formatParam.format)
		{
		case DXGI_FORMAT_R32G32B32A32_TYPELESS:
		case DXGI_FORMAT_R32G32B32A32_FLOAT:
		case DXGI_FORMAT_R32G32B32A32_UINT:
		case DXGI_FORMAT_R32G32B32A32_SINT:
			pixDataSizeByte = 16U;
			break;
		case DXGI_FORMAT_R8G8B8A8_TYPELESS:
		case DXGI_FORMAT_R8G8B8A8_UNORM:
		case DXGI_FORMAT_R8G8B8A8_UNORM_SRGB:
		case DXGI_FORMAT_R8G8B8A8_UINT:
		case DXGI_FORMAT_R8G8B8A8_SNORM:
		case DXGI_FORMAT_R8G8B8A8_SINT:
			pixDataSizeByte = 4U;
		}

		// コピー元は「フットプリント」指定
		D3D12_TEXTURE_COPY_LOCATION src{};
		src.pResource							= m_uploadBuff;
		src.Type								= D3D12_TEXTURE_COPY_TYPE_PLACED_FOOTPRINT;
		src.PlacedFootprint.Offset				= 0;
		src.PlacedFootprint.Footprint.Width		= dataParam.width;
		src.PlacedFootprint.Footprint.Height	= dataParam.height;
		src.PlacedFootprint.Footprint.Depth		= 1;
		src.PlacedFootprint.Footprint.RowPitch	= ((dataParam.width * pixDataSizeByte) + 0xff) & ~0xff;
		src.PlacedFootprint.Footprint.Format	= formatParam.format;

		// コピー先は「インデックス」指定
		D3D12_TEXTURE_COPY_LOCATION dst{};
		dst.pResource			= m_textureBuffer;
		dst.Type				= D3D12_TEXTURE_COPY_TYPE_SUBRESOURCE_INDEX;
		dst.SubresourceIndex	= 0;

		// GPU間のメモリのコピーを行う
		commandList->CopyTextureRegion(&dst, 0, 0, 0, &src, nullptr);

		// テクスチャバッファーのバリアを「コピー先」状態から「シェーダーリソース」状態に変更する
		D3D12_RESOURCE_BARRIER barrierDesc{};
		barrierDesc.Type					= D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
		barrierDesc.Flags					= D3D12_RESOURCE_BARRIER_FLAG_NONE;
		barrierDesc.Transition.pResource	= m_textureBuffer;
		barrierDesc.Transition.Subresource	= D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
		barrierDesc.Transition.StateBefore	= D3D12_RESOURCE_STATE_COPY_DEST;
		barrierDesc.Transition.StateAfter	= D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE;
		commandList->ResourceBarrier(1, &barrierDesc);
	}

	TextureBufferData::~TextureBufferData()
	{
		if (m_textureBuffer != nullptr)
		{
			m_textureBuffer->Release();
		}

		if (m_uploadBuff != nullptr)
		{
			m_uploadBuff->Release();
		}
	}

	TextureBufferData::TextureBufferData(TextureBufferData&& other) noexcept
		: m_textureSize(other.m_textureSize)
		, m_srvInitParam(other.m_srvInitParam)
		, m_textureBuffer(other.m_textureBuffer)
		, m_uploadBuff(other.m_uploadBuff)
	{
		other.m_textureBuffer = nullptr;
		other.m_uploadBuff = nullptr;
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

	D3D12_TEXTURE_COPY_LOCATION TextureBufferData::createSrcCopyLoaction() const
	{
		unsigned int pixDataSizeByte = 0U;

		switch (m_srvInitParam.format)
		{
		case DXGI_FORMAT_R32G32B32A32_TYPELESS:
		case DXGI_FORMAT_R32G32B32A32_FLOAT:
		case DXGI_FORMAT_R32G32B32A32_UINT:
		case DXGI_FORMAT_R32G32B32A32_SINT:
			pixDataSizeByte = 16U;
			break;
		case DXGI_FORMAT_R8G8B8A8_TYPELESS:
		case DXGI_FORMAT_R8G8B8A8_UNORM:
		case DXGI_FORMAT_R8G8B8A8_UNORM_SRGB:
		case DXGI_FORMAT_R8G8B8A8_UINT:
		case DXGI_FORMAT_R8G8B8A8_SNORM:
		case DXGI_FORMAT_R8G8B8A8_SINT:
			pixDataSizeByte = 4U;
		}

		D3D12_TEXTURE_COPY_LOCATION src{};
		src.pResource							= nullptr;
		src.Type								= D3D12_TEXTURE_COPY_TYPE_PLACED_FOOTPRINT;
		src.PlacedFootprint.Offset				= 0;
		src.PlacedFootprint.Footprint.Width		= static_cast<unsigned int>(m_textureSize.x);
		src.PlacedFootprint.Footprint.Height	= static_cast<unsigned int>(m_textureSize.y);
		src.PlacedFootprint.Footprint.Depth		= 1U;
		src.PlacedFootprint.Footprint.RowPitch	= ((static_cast<unsigned int>(m_textureSize.x) * pixDataSizeByte) + 0xff) & ~0xff;
		src.PlacedFootprint.Footprint.Format	= m_srvInitParam.format;

		return src;
	}
}