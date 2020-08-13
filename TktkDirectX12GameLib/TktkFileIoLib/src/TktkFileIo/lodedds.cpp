#include "TktkFileIo/lodedds.h"

#include <memory>
#include <stdexcept>
#include <algorithm>
#include <assert.h>
#include "TktkFileIo/BinaryFileReader.h"

namespace tktk
{
#ifndef MAKEFOURCC
#define MAKEFOURCC(ch0, ch1, ch2, ch3)	\
		((unsigned int)(unsigned char)(ch0) | (unsigned int)(unsigned char)(ch1) << 8)	\
		((unsigned int)(unsigned char)(ch2) << 16 | (unsigned int)(unsigned char)(ch3) << 24)
#endif // !MAKEFOURCC

#pragma pack(push, 1)

#define DDS_MAGIC 0x20534444

#define DDS_FOURCC      0x00000004	// DDPF_FOURCC
#define DDS_RGB         0x00000040	// DDPF_RGB
#define DDS_RGBA        0x00000041	// DDPF_RGB | DDPF_ALPHAPIXELS
#define DDS_LUMINANCE   0x00020000	// DDPF_LUMINANCE
#define DDS_LUMINANCEA  0x00020001	// DDPF_LUMINANCE | DDPF_ALPHAPIXELS
#define DDS_ALPHA       0x00000002	// DDPF_ALPHA
#define DDS_PAL8        0x00000020	// DDPF_PALETTEINDEXED8

#define DDS_HEADER_FLAGS_TEXTURE        0x00001007  // DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH | DDSD_PIXELFORMAT
#define DDS_HEADER_FLAGS_MIPMAP         0x00020000  // DDSD_MIPMAPCOUNT
#define DDS_HEADER_FLAGS_VOLUME         0x00800000  // DDSD_DEPTH
#define DDS_HEADER_FLAGS_PITCH          0x00000008  // DDSD_PITCH
#define DDS_HEADER_FLAGS_LINEARSIZE     0x00080000  // DDSD_LINEARSIZE

#define DDS_HEIGHT 0x00000002 // DDSD_HEIGHT
#define DDS_WIDTH  0x00000004 // DDSD_WIDTH

#define DDS_SURFACE_FLAGS_TEXTURE 0x00001000 // DDSCAPS_TEXTURE
#define DDS_SURFACE_FLAGS_MIPMAP  0x00400008 // DDSCAPS_COMPLEX | DDSCAPS_MIPMAP
#define DDS_SURFACE_FLAGS_CUBEMAP 0x00000008 // DDSCAPS_COMPLEX

#define DDS_CUBEMAP_POSITIVEX 0x00000600 // DDSCAPS2_CUBEMAP | DDSCAPS2_CUBEMAP_POSITIVEX
#define DDS_CUBEMAP_NEGATIVEX 0x00000a00 // DDSCAPS2_CUBEMAP | DDSCAPS2_CUBEMAP_NEGATIVEX
#define DDS_CUBEMAP_POSITIVEY 0x00001200 // DDSCAPS2_CUBEMAP | DDSCAPS2_CUBEMAP_POSITIVEY
#define DDS_CUBEMAP_NEGATIVEY 0x00002200 // DDSCAPS2_CUBEMAP | DDSCAPS2_CUBEMAP_NEGATIVEY
#define DDS_CUBEMAP_POSITIVEZ 0x00004200 // DDSCAPS2_CUBEMAP | DDSCAPS2_CUBEMAP_POSITIVEZ
#define DDS_CUBEMAP_NEGATIVEZ 0x00008200 // DDSCAPS2_CUBEMAP | DDSCAPS2_CUBEMAP_NEGATIVEZ

#define DDS_CUBEMAP_ALLFACES (DDS_CUBEMAP_POSITIVEX | DDS_CUBEMAP_NEGATIVEX |\
                              DDS_CUBEMAP_POSITIVEY | DDS_CUBEMAP_NEGATIVEY |\
                              DDS_CUBEMAP_POSITIVEZ | DDS_CUBEMAP_NEGATIVEZ)

#define DDS_CUBEMAP 0x00000200 // DDSCAPS2_CUBEMAP

#define DDS_FLAGS_VOLUME 0x00200000 // DDSCAPS2_VOLUME

	// 「DX10」形式のDDSファイルの追加ヘッダー形式
	typedef struct
	{
		DXGI_FORMAT dxgiFormat;
		unsigned int resourceDimension;
		unsigned int miscFlag;
		unsigned int arraySize;
		unsigned int reserved;
	} DDS_HEADER_DXT10;

#pragma pack(pop)

	// 画像データの形式毎に「１ピクセル毎に何ビットのデータを使用しているか」を取得する
	static unsigned int bitsPerPixel(DXGI_FORMAT fmt)
	{
		switch (fmt)
		{
		case DXGI_FORMAT_R32G32B32A32_TYPELESS:
		case DXGI_FORMAT_R32G32B32A32_FLOAT:
		case DXGI_FORMAT_R32G32B32A32_UINT:
		case DXGI_FORMAT_R32G32B32A32_SINT:
			return 128U;

		case DXGI_FORMAT_R32G32B32_TYPELESS:
		case DXGI_FORMAT_R32G32B32_FLOAT:
		case DXGI_FORMAT_R32G32B32_UINT:
		case DXGI_FORMAT_R32G32B32_SINT:
			return 96U;

		case DXGI_FORMAT_R16G16B16A16_TYPELESS:
		case DXGI_FORMAT_R16G16B16A16_FLOAT:
		case DXGI_FORMAT_R16G16B16A16_UNORM:
		case DXGI_FORMAT_R16G16B16A16_UINT:
		case DXGI_FORMAT_R16G16B16A16_SNORM:
		case DXGI_FORMAT_R16G16B16A16_SINT:
		case DXGI_FORMAT_R32G32_TYPELESS:
		case DXGI_FORMAT_R32G32_FLOAT:
		case DXGI_FORMAT_R32G32_UINT:
		case DXGI_FORMAT_R32G32_SINT:
		case DXGI_FORMAT_R32G8X24_TYPELESS:
		case DXGI_FORMAT_D32_FLOAT_S8X24_UINT:
		case DXGI_FORMAT_R32_FLOAT_X8X24_TYPELESS:
		case DXGI_FORMAT_X32_TYPELESS_G8X24_UINT:
			return 64U;

		case DXGI_FORMAT_R10G10B10A2_TYPELESS:
		case DXGI_FORMAT_R10G10B10A2_UNORM:
		case DXGI_FORMAT_R10G10B10A2_UINT:
		case DXGI_FORMAT_R11G11B10_FLOAT:
		case DXGI_FORMAT_R8G8B8A8_TYPELESS:
		case DXGI_FORMAT_R8G8B8A8_UNORM:
		case DXGI_FORMAT_R8G8B8A8_UNORM_SRGB:
		case DXGI_FORMAT_R8G8B8A8_UINT:
		case DXGI_FORMAT_R8G8B8A8_SNORM:
		case DXGI_FORMAT_R8G8B8A8_SINT:
		case DXGI_FORMAT_R16G16_TYPELESS:
		case DXGI_FORMAT_R16G16_FLOAT:
		case DXGI_FORMAT_R16G16_UNORM:
		case DXGI_FORMAT_R16G16_UINT:
		case DXGI_FORMAT_R16G16_SNORM:
		case DXGI_FORMAT_R16G16_SINT:
		case DXGI_FORMAT_R32_TYPELESS:
		case DXGI_FORMAT_D32_FLOAT:
		case DXGI_FORMAT_R32_FLOAT:
		case DXGI_FORMAT_R32_UINT:
		case DXGI_FORMAT_R32_SINT:
		case DXGI_FORMAT_R24G8_TYPELESS:
		case DXGI_FORMAT_D24_UNORM_S8_UINT:
		case DXGI_FORMAT_R24_UNORM_X8_TYPELESS:
		case DXGI_FORMAT_X24_TYPELESS_G8_UINT:
		case DXGI_FORMAT_R9G9B9E5_SHAREDEXP:
		case DXGI_FORMAT_R8G8_B8G8_UNORM:
		case DXGI_FORMAT_G8R8_G8B8_UNORM:
		case DXGI_FORMAT_B8G8R8A8_UNORM:
		case DXGI_FORMAT_B8G8R8X8_UNORM:
		case DXGI_FORMAT_R10G10B10_XR_BIAS_A2_UNORM:
		case DXGI_FORMAT_B8G8R8A8_TYPELESS:
		case DXGI_FORMAT_B8G8R8A8_UNORM_SRGB:
		case DXGI_FORMAT_B8G8R8X8_TYPELESS:
		case DXGI_FORMAT_B8G8R8X8_UNORM_SRGB:
			return 32U;

		case DXGI_FORMAT_R8G8_TYPELESS:
		case DXGI_FORMAT_R8G8_UNORM:
		case DXGI_FORMAT_R8G8_UINT:
		case DXGI_FORMAT_R8G8_SNORM:
		case DXGI_FORMAT_R8G8_SINT:
		case DXGI_FORMAT_R16_TYPELESS:
		case DXGI_FORMAT_R16_FLOAT:
		case DXGI_FORMAT_D16_UNORM:
		case DXGI_FORMAT_R16_UNORM:
		case DXGI_FORMAT_R16_UINT:
		case DXGI_FORMAT_R16_SNORM:
		case DXGI_FORMAT_R16_SINT:
		case DXGI_FORMAT_B5G6R5_UNORM:
		case DXGI_FORMAT_B5G5R5A1_UNORM:
		case DXGI_FORMAT_B4G4R4A4_UNORM:
			return 16U;

		case DXGI_FORMAT_R8_TYPELESS:
		case DXGI_FORMAT_R8_UNORM:
		case DXGI_FORMAT_R8_UINT:
		case DXGI_FORMAT_R8_SNORM:
		case DXGI_FORMAT_R8_SINT:
		case DXGI_FORMAT_A8_UNORM:
			return 8U;

		case DXGI_FORMAT_R1_UNORM:
			return 1U;

		case DXGI_FORMAT_BC1_TYPELESS:
		case DXGI_FORMAT_BC1_UNORM:
		case DXGI_FORMAT_BC1_UNORM_SRGB:
		case DXGI_FORMAT_BC4_TYPELESS:
		case DXGI_FORMAT_BC4_UNORM:
		case DXGI_FORMAT_BC4_SNORM:
			return 4U;

		case DXGI_FORMAT_BC2_TYPELESS:
		case DXGI_FORMAT_BC2_UNORM:
		case DXGI_FORMAT_BC2_UNORM_SRGB:
		case DXGI_FORMAT_BC3_TYPELESS:
		case DXGI_FORMAT_BC3_UNORM:
		case DXGI_FORMAT_BC3_UNORM_SRGB:
		case DXGI_FORMAT_BC5_TYPELESS:
		case DXGI_FORMAT_BC5_UNORM:
		case DXGI_FORMAT_BC5_SNORM:
		case DXGI_FORMAT_BC6H_TYPELESS:
		case DXGI_FORMAT_BC6H_UF16:
		case DXGI_FORMAT_BC6H_SF16:
		case DXGI_FORMAT_BC7_TYPELESS:
		case DXGI_FORMAT_BC7_UNORM:
		case DXGI_FORMAT_BC7_UNORM_SRGB:
			return 8U;

		default:
			return 0U;
		}
	}

#define ISBITMASK(r, g, b, a) (ddpf.RBitMask == r && ddpf.GBitMask == g && ddpf.BBitMask == b && ddpf.ABitMask == a)

	static DXGI_FORMAT getDXGIFormat(const DDS_PIXELFORMAT& ddpf)
	{
		if (ddpf.flags & DDS_RGB)
		{
			switch (ddpf.RGBBitCount)
			{
			case 32:

				if (ISBITMASK(0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000))
				{
					return DXGI_FORMAT_R8G8B8A8_UNORM;
				}

				if (ISBITMASK(0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000))
				{
					return DXGI_FORMAT_B8G8R8A8_UNORM;
				}

				if (ISBITMASK(0x00ff0000, 0x0000ff00, 0x000000ff, 0x00000000))
				{
					return DXGI_FORMAT_B8G8R8X8_UNORM;
				}

				if (ISBITMASK(0x3ff00000, 0x000ffc00, 0x000003ff, 0xc0000000))
				{
					return DXGI_FORMAT_R10G10B10A2_UNORM;
				}

				if (ISBITMASK(0x0000ffff, 0xffff0000, 0x00000000, 0x00000000))
				{
					return DXGI_FORMAT_R16G16_UNORM;
				}

				if (ISBITMASK(0xffffffff, 0x00000000, 0x00000000, 0x00000000))
				{
					return DXGI_FORMAT_R32_FLOAT;
				}

				break;

			case 24:

				break;

			case 16:

				if (ISBITMASK(0x7c00, 0x03e0, 0x001f, 0x8000))
				{
					return DXGI_FORMAT_B5G5R5A1_UNORM;
				}

				if (ISBITMASK(0xf800, 0x07e0, 0x001f, 0x0000))
				{
					return DXGI_FORMAT_B5G6R5_UNORM;
				}

				if (ISBITMASK(0x0f00, 0x00f0, 0x000f, 0xf000))
				{
					return DXGI_FORMAT_B4G4R4A4_UNORM;
				}

				break;

			default:
				break;
			}
		}
		else if (ddpf.flags & DDS_LUMINANCE)
		{
			if (ddpf.RGBBitCount == 8)
			{
				if (ISBITMASK(0x000000ff, 0x00000000, 0x00000000, 0x00000000))
				{
					return DXGI_FORMAT_R8_UNORM;
				}
			}

			if (ddpf.RGBBitCount == 16)
			{
				if (ISBITMASK(0x0000ffff, 0x00000000, 0x00000000, 0x00000000))
				{
					return DXGI_FORMAT_R16_UNORM;
				}

				if (ISBITMASK(0x000000ff, 0x00000000, 0x00000000, 0x0000ff00))
				{
					return DXGI_FORMAT_R8G8_UNORM;
				}
			}
		}
		else if (ddpf.flags & DDS_ALPHA)
		{
			if (ddpf.RGBBitCount == 8)
			{
				return DXGI_FORMAT_A8_UNORM;
			}
		}
		else if (ddpf.flags & DDS_FOURCC)
		{
			if (ddpf.fourCC == MAKEFOURCC('D', 'X', 'T', '1'))
			{
				return DXGI_FORMAT_BC1_UNORM;
			}

			if (ddpf.fourCC == MAKEFOURCC('D', 'X', 'T', '3'))
			{
				return DXGI_FORMAT_BC2_UNORM;
			}

			if (ddpf.fourCC == MAKEFOURCC('D', 'X', 'T', '5'))
			{
				return DXGI_FORMAT_BC3_UNORM;
			}

			if (ddpf.fourCC == MAKEFOURCC('D', 'X', 'T', '2'))
			{
				return DXGI_FORMAT_BC2_UNORM;
			}

			if (ddpf.fourCC == MAKEFOURCC('D', 'X', 'T', '4'))
			{
				return DXGI_FORMAT_BC3_UNORM;
			}

			if (ddpf.fourCC == MAKEFOURCC('A', 'T', 'I', '1'))
			{
				return DXGI_FORMAT_BC4_UNORM;
			}

			if (ddpf.fourCC == MAKEFOURCC('B', 'C', '4', 'U'))
			{
				return DXGI_FORMAT_BC4_UNORM;
			}

			if (ddpf.fourCC == MAKEFOURCC('B', 'C', '4', 'S'))
			{
				return DXGI_FORMAT_BC4_SNORM;
			}

			if (ddpf.fourCC == MAKEFOURCC('A', 'T', 'I', '2'))
			{
				return DXGI_FORMAT_BC4_UNORM;
			}

			if (ddpf.fourCC == MAKEFOURCC('B', 'C', '5', 'U'))
			{
				return DXGI_FORMAT_BC5_UNORM;
			}

			if (ddpf.fourCC == MAKEFOURCC('B', 'C', '5', 'S'))
			{
				return DXGI_FORMAT_BC5_SNORM;
			}

			if (ddpf.fourCC == MAKEFOURCC('R', 'G', 'B', 'G'))
			{
				return DXGI_FORMAT_R8G8_B8G8_UNORM;;
			}

			if (ddpf.fourCC == MAKEFOURCC('G', 'R', 'G', 'B'))
			{
				return DXGI_FORMAT_G8R8_G8B8_UNORM;;
			}

			switch (ddpf.fourCC)
			{
			case 36:

				return DXGI_FORMAT_R16G16B16A16_UNORM;

			case 110:

				return DXGI_FORMAT_R16G16B16A16_SNORM;

			case 111:

				return DXGI_FORMAT_R16_FLOAT;

			case 112:

				return DXGI_FORMAT_R16G16_FLOAT;

			case 113:

				return DXGI_FORMAT_R16G16B16A16_FLOAT;

			case 114:

				return DXGI_FORMAT_R32_FLOAT;

			case 115:

				return DXGI_FORMAT_R32G32_FLOAT;

			case 116:

				return DXGI_FORMAT_R32G32B32A32_FLOAT;
			}
		}

		return DXGI_FORMAT_UNKNOWN;
	}

	/*static HRESULT createD3DResources(
		ID3D11Device* device,
		unsigned int resDim,
		unsigned int width,
		unsigned int height,
		unsigned int depth,
		unsigned int mipCount,
		unsigned int arraySize,
		DXGI_FORMAT format,
		bool isCubeMap,
		D3D11_SUBRESOURCE_DATA* initData,
		ID3D11Resource** outTexture,
		ID3D11ShaderResourceView ** outTextureView
	)
	{
		if (!device || !initData)
		{
			return E_INVALIDARG;
		}

		HRESULT hr = E_FAIL;

		switch (resDim)
		{
		case D3D11_RESOURCE_DIMENSION_TEXTURE1D:
			{
				D3D11_TEXTURE1D_DESC desc;
				desc.Width = width;
				desc.MipLevels = mipCount;
				desc.ArraySize = arraySize;
				desc.Format = format;
				desc.CPUAccessFlags = 0U;
				desc.MiscFlags = 0U;

				ID3D11Texture1D* tex = nullptr;
				hr = device->CreateTexture1D(&desc, initData, &tex);

				if (SUCCEEDED(hr) && tex != 0)
				{
					if (outTextureView != 0)
					{
						D3D11_SHADER_RESOURCE_VIEW_DESC SRVDesc;
						memset(&SRVDesc, 0, sizeof(SRVDesc));
						SRVDesc.Format = format;

						if (arraySize > 1U)
						{
							SRVDesc.ViewDimension = D3D_SRV_DIMENSION_TEXTURE1DARRAY;
							SRVDesc.Texture1DArray.MipLevels = desc.MipLevels;
							SRVDesc.Texture1DArray.ArraySize = arraySize;
						}
						else
						{
							SRVDesc.ViewDimension = D3D_SRV_DIMENSION_TEXTURE1D;
							SRVDesc.Texture1D.MipLevels = desc.MipLevels;
						}

						hr = device->CreateShaderResourceView(tex, &SRVDesc, outTextureView);

						if (FAILED(hr))
						{
							tex->Release();
							return hr;
						}
					}

					if (outTexture != 0)
					{
						*outTexture = tex;
					}
					else
					{
						tex->Release();
					}
				}
			}
			break;

		case D3D11_RESOURCE_DIMENSION_TEXTURE2D:
			{
				D3D11_TEXTURE2D_DESC desc;
				desc.Width = width;
				desc.Height = height;
				desc.MipLevels = mipCount;
				desc.ArraySize = arraySize;
				desc.Format = format;
				desc.SampleDesc.Count = 1U;
				desc.SampleDesc.Quality = 0U;
				desc.Usage = D3D11_USAGE_DEFAULT;
				desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
				desc.CPUAccessFlags = 0U;
				desc.MiscFlags = (isCubeMap) ? D3D11_RESOURCE_MISC_TEXTURECUBE : 0U;

				ID3D11Texture2D* tex = nullptr;
				hr = device->CreateTexture2D(&desc, initData, &tex);

				if (SUCCEEDED(hr) && tex != 0)
				{
					if (outTextureView != 0)
					{
						D3D11_SHADER_RESOURCE_VIEW_DESC SRVDesc;
						memset(&SRVDesc, 0, sizeof(SRVDesc));
						SRVDesc.Format = format;

						if (isCubeMap)
						{
							if (arraySize > 6)
							{
								SRVDesc.ViewDimension = D3D_SRV_DIMENSION_TEXTURECUBEARRAY;
								SRVDesc.TextureCubeArray.MipLevels = desc.MipLevels;
								SRVDesc.TextureCubeArray.NumCubes = arraySize / 6U;
							}
							else
							{
								SRVDesc.ViewDimension = D3D_SRV_DIMENSION_TEXTURECUBE;
								SRVDesc.TextureCube.MipLevels = desc.MipLevels;
							}
						}
						else if (arraySize > 1U)
						{
							SRVDesc.ViewDimension = D3D_SRV_DIMENSION_TEXTURE2DARRAY;
							SRVDesc.Texture2DArray.MipLevels = desc.MipLevels;
							SRVDesc.Texture2DArray.ArraySize = arraySize;
						}
						else
						{
							SRVDesc.ViewDimension = D3D_SRV_DIMENSION_TEXTURE2D;
							SRVDesc.Texture2D.MipLevels = desc.MipLevels;
						}

						hr = device->CreateShaderResourceView(tex, &SRVDesc, outTextureView);

						if (FAILED(hr))
						{
							tex->Release();
							return hr;
						}
					}

					if (outTexture != 0)
					{
						*outTexture = tex;
					}
					else
					{
						tex->Release();
					}
				}
			}
			break;

		case D3D11_RESOURCE_DIMENSION_TEXTURE3D:
			{
				D3D11_TEXTURE3D_DESC desc;
				desc.Width = width;
				desc.Height = height;
				desc.Depth = depth;
				desc.MipLevels = mipCount;
				desc.Format = format;
				desc.Usage = D3D11_USAGE_DEFAULT;
				desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
				desc.CPUAccessFlags = 0U;
				desc.MiscFlags = 0U;

				ID3D11Texture3D* tex = nullptr;
				hr = device->CreateTexture3D(&desc, initData, &tex);

				if (SUCCEEDED(hr) && tex != 0)
				{
					if (outTextureView != 0)
					{
						D3D11_SHADER_RESOURCE_VIEW_DESC SRVDesc;
						memset(&SRVDesc, 0, sizeof(SRVDesc));
						SRVDesc.Format = format;
						SRVDesc.ViewDimension = D3D_SRV_DIMENSION_TEXTURE3D;
						SRVDesc.Texture3D.MipLevels = desc.MipLevels;

						hr = device->CreateShaderResourceView(tex, &SRVDesc, outTextureView);

						if (FAILED(hr))
						{
							tex->Release();
							return hr;
						}
					}

					if (outTexture != 0)
					{
						*outTexture = tex;
					}
					else
					{
						tex->Release();
					}
				}
			}
			break;
		}
		return hr;
	}*/

	void lodedds::load(loadData* outData, const std::string & fileName)
	{
		// 生のDDSファイルデータを読み込む
		BinaryFileReader::fileRead(fileName, &outData->rawDdsFileData);

		if (outData->rawDdsFileData.size() < (sizeof(unsigned int) + sizeof(DDS_HEADER)))
		{
			throw std::runtime_error("lode dds file error");
		}

		// バイナリデータの先頭にDDSファイルを意味するデータが無かったらエラー
		unsigned int dwMagicNumber = *(const unsigned int*)(outData->rawDdsFileData.data());
		if (dwMagicNumber != DDS_MAGIC)
		{
			throw std::runtime_error("lode dds file error");
		}

		// DDSデータのヘッダ部分のデータ構造を取得する
		const DDS_HEADER* header = reinterpret_cast<const DDS_HEADER*>(outData->rawDdsFileData.data() + sizeof(unsigned int));

		if (header->size != sizeof(DDS_HEADER) ||
			header->ddspf.size != sizeof(DDS_PIXELFORMAT))
		{
			throw std::runtime_error("lode dds file error");
		}

		bool bDXT10Header = false;
		if ((header->ddspf.flags & DDS_FOURCC) &&
			(header->ddspf.fourCC == MAKEFOURCC('D', 'X', '1', '0')))
		{
			if (outData->rawDdsFileData.size() < (sizeof(DDS_HEADER) + sizeof(unsigned int) + sizeof(DDS_HEADER_DXT10)))
			{
				throw std::runtime_error("lode dds file error");
			}
			bDXT10Header = true;
		}

		int offset = static_cast<int>(sizeof(unsigned int) + sizeof(DDS_HEADER) + (bDXT10Header ? sizeof(DDS_HEADER_DXT10) : 0));

		// TODO : 最後の引数の意味を調べる
		createTextureFromDDS(outData, header, outData->rawDdsFileData.data() + offset, outData->rawDdsFileData.size() - offset, 0);
	}

	void lodedds::createTextureFromDDS(loadData* outData, const DDS_HEADER * header, const unsigned char * bitData, unsigned int bitSize, unsigned int maxSize)
	{
		// DDSファイルから画像データの横の長さを読み込む
		unsigned int width = header->width;
		// DDSファイルから画像データの縦の長さを読み込む
		unsigned int height = header->height;
		// DDSファイルから画像データの奥の長さ（3D画像データのみ）を読み込む
		unsigned int depth = header->depth;

		// DDSファイルからミップマップの数を読み込む（0個はありえないので0個だったら1個にする）
		unsigned int mipCount = header->mipMapCount;
		if (mipCount == 0U) mipCount = 1U;
		// ミップマップの数が扱える最大値を超えていたらエラー
		if (mipCount > D3D11_REQ_MIP_LEVELS) throw std::runtime_error("lode dds file error");

		// 画像データの情報を格納する変数を初期化
		unsigned int resDim = D3D11_RESOURCE_DIMENSION_UNKNOWN;
		unsigned int arraySize = 1;
		DXGI_FORMAT format = DXGI_FORMAT_UNKNOWN;
		bool isCubeMap = false;

		// DDSファイルの形式が「DX10」だったら
		if ((header->ddspf.flags & DDS_FOURCC) && header->ddspf.fourCC == (MAKEFOURCC('D', 'X', '1', '0')))
		{
			// 「DX10」形式の追加ヘッダー情報を取得
			const DDS_HEADER_DXT10* d3d10dxt = reinterpret_cast<const DDS_HEADER_DXT10*>((const char*)header + sizeof(DDS_HEADER));

			// 何個の画像データが存在するかを取得する（データが存在しなければエラー）
			arraySize = d3d10dxt->arraySize;
			if (arraySize == 0) throw std::runtime_error("lode dds file error");

			// 画像データのフォーマットを取得する（正しくないフォーマットならばエラー）
			format = d3d10dxt->dxgiFormat;
			if (bitsPerPixel(format) == 0) throw std::runtime_error("lode dds file error");

			// 何次元のテクスチャかを取得し、分岐する
			resDim = d3d10dxt->resourceDimension;
			switch (resDim)
			{
				// １次元テクスチャならば
			case D3D11_RESOURCE_DIMENSION_TEXTURE1D:

				// 画像の高さの情報が存在するならばエラー
				if ((header->flags & DDS_HEIGHT) && height != 1) throw std::runtime_error("lode dds file error");

				// 画像の高さの値と奥行きの値は常に１
				height = 1;
				depth = 1;
				break;

				// ２次元テクスチャならば
			case D3D11_RESOURCE_DIMENSION_TEXTURE2D:

				// キューブマップテクスチャならば
				if (d3d10dxt->miscFlag & D3D11_RESOURCE_MISC_TEXTURECUBE)
				{
					// 立方体の各面分（６面）のデータサイズを指定する
					arraySize *= 6;
					// キューブマップフラグを立てる
					isCubeMap = true;
				}
				// 画像の奥行きの値は常に１
				depth = 1;
				break;

				// ３次元テクスチャならば
			case D3D11_RESOURCE_DIMENSION_TEXTURE3D:

				// 「DDS_HEADER_FLAGS_VOLUME」が立っていなければエラー
				if (!(header->flags & DDS_HEADER_FLAGS_VOLUME)) throw std::runtime_error("lode dds file error");

				// ３次元テクスチャは常に単一のテクスチャデータを持つ
				if (arraySize > 1) throw std::runtime_error("lode dds file error");
				break;

				// 謎な形式だったらエラー
			default: throw std::runtime_error("lode dds file error");
			}
		}
		else
		{
			// 画像データのフォーマットを取得する（正しくないフォーマットならばエラー）
			format = getDXGIFormat(header->ddspf);
			if (format == DXGI_FORMAT_UNKNOWN) throw std::runtime_error("lode dds file error");

			// 「DDS_HEADER_FLAGS_VOLUME」が立っていたら
			if (header->flags & DDS_HEADER_FLAGS_VOLUME)
			{
				// ３次元テクスチャとして扱う
				resDim = D3D11_RESOURCE_DIMENSION_TEXTURE3D;
			}
			else
			{
				// キューブマップテクスチャフラグが立っていたら
				if (header->caps2 & DDS_CUBEMAP)
				{
					// キューブマップとして必要なフラグが立っていなかったらエラー
					if ((header->caps2 & DDS_CUBEMAP_ALLFACES) != DDS_CUBEMAP_ALLFACES) throw std::runtime_error("lode dds file error");

					// 立方体の各面分（６面）のデータサイズを指定する
					arraySize *= 6;
					// キューブマップフラグを立てる
					isCubeMap = true;
				}

				// 画像の奥行きの値は常に１
				depth = 1;
				// ２次元テクスチャとして扱う
				resDim = D3D11_RESOURCE_DIMENSION_TEXTURE2D;
			}

			// TODO : 意味を理解する
			// なんだかよく分からんが、フォーマットが正しくなければエラー
			assert(bitsPerPixel(format) != 0U);
		}

		// 何次元のテクスチャかで分岐する
		switch (resDim)
		{
			// １次元テクスチャならば
		case D3D11_RESOURCE_DIMENSION_TEXTURE1D:

			// 画像データの数か横幅が最大値を超えていたらエラー
			if ((arraySize > D3D11_REQ_TEXTURE1D_ARRAY_AXIS_DIMENSION) || (width > D3D11_REQ_TEXTURE1D_U_DIMENSION)) throw std::runtime_error("lode dds file error");
			break;

			// ２次元テクスチャならば
		case D3D11_RESOURCE_DIMENSION_TEXTURE2D:

			// キューブマップテクスチャの場合
			if (isCubeMap)
			{
				// 画像データの数、横幅、立幅いずれかが最大値を超えていたらエラー
				if ((arraySize > D3D11_REQ_TEXTURE2D_ARRAY_AXIS_DIMENSION) || (width > D3D11_REQ_TEXTURECUBE_DIMENSION) || (height > D3D11_REQ_TEXTURECUBE_DIMENSION)) throw std::runtime_error("lode dds file error");
			}
			// キューブマップテクスチャではない場合の画像データの数、横幅、立幅いずれかが最大値を超えていたらエラー
			else if ((arraySize > D3D11_REQ_TEXTURE2D_ARRAY_AXIS_DIMENSION) || (width > D3D11_REQ_TEXTURE2D_U_OR_V_DIMENSION) || (height > D3D11_REQ_TEXTURE2D_U_OR_V_DIMENSION)) throw std::runtime_error("lode dds file error");
			break;

			// ３次元テクスチャならば
		case D3D11_RESOURCE_DIMENSION_TEXTURE3D:

			// 画像データの数、横幅、立幅、奥行きいずれかが最大値を超えていたらエラー
			if ((arraySize > 1U) || (width > D3D11_REQ_TEXTURE3D_U_V_OR_W_DIMENSION) || (height > D3D11_REQ_TEXTURE3D_U_V_OR_W_DIMENSION) || (depth > D3D11_REQ_TEXTURE3D_U_V_OR_W_DIMENSION)) throw std::runtime_error("lode dds file error");
			break;
		}

		fillInitData(outData, width, height, depth, mipCount, arraySize, format, maxSize, bitSize, bitData);

		(*outData).resourceDimension = static_cast<D3D11_RESOURCE_DIMENSION>(resDim);
		(*outData).mipCount = mipCount - outData->skipMip;
		(*outData).arraySize = arraySize;
		(*outData).format = format;
		(*outData).isCubeMap = isCubeMap;

		/*
		// TODO : この1行の意味を考える
		if (FAILED(hr) && !maxSize && (mipCount > 1))
		{
			switch (device->GetFeatureLevel())
			{
			case D3D_FEATURE_LEVEL_9_1:
			case D3D_FEATURE_LEVEL_9_2:

				if (isCubeMap)
				{
					maxSize = D3D_FL9_1_REQ_TEXTURECUBE_DIMENSION;
				}
				else
				{
					maxSize = (resDim == D3D11_RESOURCE_DIMENSION_TEXTURE3D)
						? D3D_FL9_1_REQ_TEXTURE3D_U_V_OR_W_DIMENSION
						: D3D_FL9_1_REQ_TEXTURE2D_U_OR_V_DIMENSION;
				}
				break;

			case D3D_FEATURE_LEVEL_9_3:

				maxSize = (resDim == D3D11_RESOURCE_DIMENSION_TEXTURE3D)
					? D3D_FL9_1_REQ_TEXTURE3D_U_V_OR_W_DIMENSION
					: D3D_FL9_3_REQ_TEXTURE2D_U_OR_V_DIMENSION;
				break;

			default:

				maxSize = (resDim == D3D11_RESOURCE_DIMENSION_TEXTURE3D)
					? D3D10_REQ_TEXTURE3D_U_V_OR_W_DIMENSION
					: D3D10_REQ_TEXTURE2D_U_OR_V_DIMENSION;
				break;
			}

			fillInitData(width, height, depth, mipCount, arraySize, format, maxSize, bitSize, bitData, &twidth, &theight, &tdepth, &skipMip, initData.get());

			hr = createD3DResources(device, resDim, twidth, theight, tdepth, mipCount - skipMip, arraySize, format, isCubeMap, initData.get(), outTexture, outTextureView);
		}*/
	}

	void lodedds::fillInitData(
		loadData* outData,
		unsigned int width,
		unsigned int height,
		unsigned int depth,
		unsigned int mipCount,
		unsigned int arraySize,
		DXGI_FORMAT format,
		unsigned int maxSize,
		unsigned int bitSize,
		const unsigned char * bitData
	)
	{
		// 結果出力用変数を初期化する
		(*outData).width = 0U;
		(*outData).height = 0U;
		(*outData).depth = 0U;
		(*outData).skipMip = 0U;
		(*outData).subrescorceDataArray.reserve(mipCount * arraySize);

		// 画像データの総バイト数
		unsigned int NumBytes = 0U;
		// 画像データ横一列のバイト数
		unsigned int RowBytes = 0U;
		// 画像データ縦の長さ（列が何列あるか？）
		unsigned int NumRows = 0U;

		// 使用する画像データの開始位置
		const unsigned char* pSrcBits = bitData;

		// 使用する画像データの終了位置
		const unsigned char* pEndBits = bitData + bitSize;

		// 画像データの数だけループする
		for (unsigned int i = 0U; i < arraySize; i++)
		{
			// 横幅、立幅、奥行きの一時保存変数
			unsigned int w = width;
			unsigned int h = height;
			unsigned int d = depth;

			// ミップマップの数だけループする
			for (unsigned int j = 0U; j < mipCount; j++)
			{
				// フォーマットに対応した読み込むデータの幅を取得
				getSurfaceInfo(w, h, format, &NumBytes, &RowBytes, &NumRows);

				if ((mipCount <= 1) || !maxSize || (w <= maxSize && h <= maxSize && d <= maxSize))
				{
					//  結果出力用変数の横幅が0だったら画像サイズのデータを入力する
					if (!(*outData).width)
					{
						(*outData).width = w;
						(*outData).height = h;
						(*outData).depth = d;
					}

					// 結果出力用変数の画像データのデータを追加する
					D3D11_SUBRESOURCE_DATA subrescorceData{};
					subrescorceData.pSysMem = (const void*)pSrcBits;
					subrescorceData.SysMemPitch = RowBytes;
					subrescorceData.SysMemSlicePitch = NumBytes;
					(*outData).subrescorceDataArray.push_back(subrescorceData);
				}
				else
				{
					++(*outData).skipMip;
				}

				// 使用する画像データの範囲を超過して使用しようとしている場合エラー
				if (pSrcBits + (NumBytes * d) > pEndBits)
				{
					throw std::runtime_error("lode dds file error");
				}

				// 使用する画像データの開始位置を画像データの大きさ分だけ移動
				pSrcBits += NumBytes * d;

				// 横幅、立幅、奥行きの一時保存変数を右に１つビットシフトする
				w = w >> 1;
				h = h >> 1;
				d = d >> 1;

				// 0になっていたら1にする
				if (w == 0U) w = 1U;
				if (h == 0U) h = 1U;
				if (d == 0U) d = 1U;
			}
		}

		// 画像データが１つも読み込めていなければエラー
		if ((*outData).subrescorceDataArray.empty()) throw std::runtime_error("lode dds file error");
	}

	void lodedds::getSurfaceInfo(unsigned int width, unsigned int height, DXGI_FORMAT format, unsigned int * outNumBytes, unsigned int * outRowBytes, unsigned int * outNumRows)
	{
		// 画像データの総バイト数
		unsigned int numBytes = 0U;
		// 画像データ横一列のバイト数
		unsigned int rowBytes = 0U;
		// 画像データ縦の長さ（列が何列あるか？）
		unsigned int numRows = 0U;

		// BCフォーマットかを表すフラグ
		bool bc = false;
		// パックされているかを表すフラグ
		bool packed = false;

		// BCフォーマットの時に使用する１ピクセル当たりのビット数
		unsigned int bcnumBytesPerBlock = 0U;

		// フォーマット毎に分岐する
		switch (format)
		{
		case DXGI_FORMAT_BC1_TYPELESS:
		case DXGI_FORMAT_BC1_UNORM:
		case DXGI_FORMAT_BC1_UNORM_SRGB:
		case DXGI_FORMAT_BC4_TYPELESS:
		case DXGI_FORMAT_BC4_UNORM:
		case DXGI_FORMAT_BC4_SNORM:
			bc = true;
			bcnumBytesPerBlock = 8U;
			break;

		case DXGI_FORMAT_BC2_TYPELESS:
		case DXGI_FORMAT_BC2_UNORM:
		case DXGI_FORMAT_BC2_UNORM_SRGB:
		case DXGI_FORMAT_BC3_TYPELESS:
		case DXGI_FORMAT_BC3_UNORM:
		case DXGI_FORMAT_BC3_UNORM_SRGB:
		case DXGI_FORMAT_BC5_TYPELESS:
		case DXGI_FORMAT_BC5_UNORM:
		case DXGI_FORMAT_BC5_SNORM:
		case DXGI_FORMAT_BC6H_TYPELESS:
		case DXGI_FORMAT_BC6H_UF16:
		case DXGI_FORMAT_BC6H_SF16:
		case DXGI_FORMAT_BC7_TYPELESS:
		case DXGI_FORMAT_BC7_UNORM:
		case DXGI_FORMAT_BC7_UNORM_SRGB:
			bc = true;
			bcnumBytesPerBlock = 16U;
			break;

		case DXGI_FORMAT_R8G8_B8G8_UNORM:
		case DXGI_FORMAT_G8R8_G8B8_UNORM:
			packed = true;
			break;
		}

		// BCフォーマットだったら
		if (bc)
		{
			// 画像データの横の長さを求める
			unsigned int numBlocksWide = 0U;
			if (width > 0U) numBlocksWide = std::max<unsigned int>(1U, (width + 3U) / 4U);

			// 画像データの縦の長さを求める
			unsigned int numBlocksHigh = 0U;
			if (height > 0U) numBlocksHigh = std::max<unsigned int>(1U, (height + 3U) / 4U);

			rowBytes = numBlocksWide * bcnumBytesPerBlock;
			numRows = numBlocksHigh;
		}
		// パックされていたら
		else if (packed)
		{
			rowBytes = ((width + 1) >> 1) * 4;
			numRows = height;
		}
		// それ以外なら
		else
		{
			// １ピクセル当たりのビット数を取得する
			unsigned int bpp = bitsPerPixel(format);
			rowBytes = (width * bpp + 7) / 8;
			numRows = height;
		}

		// 画像データの総バイトを計算する
		numBytes = rowBytes * numRows;

		// 各値を出力用変数に代入する
		if (outNumBytes) *outNumBytes = numBytes;
		if (outRowBytes) *outRowBytes = rowBytes;
		if (outNumRows) *outNumRows = numRows;
	}
}