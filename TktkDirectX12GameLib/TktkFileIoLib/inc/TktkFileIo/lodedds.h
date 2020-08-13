#ifndef LODE_DDS_H_
#define LODE_DDS_H_

#include <string>
#include <vector>
#include <d3d11.h>

namespace tktkFileIo
{
#pragma pack(push, 1)
	struct DDS_PIXELFORMAT
	{
		unsigned int size;
		unsigned int flags;
		unsigned int fourCC;
		unsigned int RGBBitCount;
		unsigned int RBitMask;
		unsigned int GBitMask;
		unsigned int BBitMask;
		unsigned int ABitMask;
	};

	// DDSファイルのヘッダーの形式
	struct DDS_HEADER
	{
		unsigned int size;
		unsigned int flags;
		unsigned int height;
		unsigned int width;
		unsigned int pitchOrLinearSize;
		unsigned int depth;
		unsigned int mipMapCount;
		unsigned int reserved1[11];
		DDS_PIXELFORMAT ddspf;
		unsigned int caps;
		unsigned int caps2;
		unsigned int caps3;
		unsigned int caps4;
		unsigned int reserved2;
	};
#pragma pack(pop)

	class lodedds
	{
	public:

		struct loadData
		{
			std::vector<unsigned char> rawDdsFileData;
			std::vector<D3D11_SUBRESOURCE_DATA> subrescorceDataArray;
			unsigned int width;
			unsigned int height;
			unsigned int depth;
			unsigned int skipMip;

			D3D11_RESOURCE_DIMENSION resourceDimension;
			unsigned int mipCount;
			unsigned int arraySize;
			DXGI_FORMAT format;
			bool isCubeMap;
		};

	public:

		static void load(loadData* outData, const std::string& fileName);

	private:

		static void createTextureFromDDS(loadData* outData, const DDS_HEADER* header, const unsigned char* bitData, unsigned int bitSize, unsigned int maxSize);

		static void fillInitData(
			loadData* outData,
			unsigned int width,
			unsigned int height,
			unsigned int depth,
			unsigned int mipCount,
			unsigned int arraySize,
			DXGI_FORMAT format,
			unsigned int maxSize,
			unsigned int bitSize,
			const unsigned char* bitData
		);

		static void getSurfaceInfo(
			unsigned int width,
			unsigned int height,
			DXGI_FORMAT format,
			unsigned int* outNumBytes,
			unsigned int* outRowBytes,
			unsigned int* outNumRows
		);
	};
}
#endif // !LODE_DDS_H_