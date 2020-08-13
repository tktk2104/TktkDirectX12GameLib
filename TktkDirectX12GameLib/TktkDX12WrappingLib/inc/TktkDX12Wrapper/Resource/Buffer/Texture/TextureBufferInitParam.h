#ifndef TEXTURE_BUFFER_INIT_PARAM_H_
#define TEXTURE_BUFFER_INIT_PARAM_H_

#include <vector>
#include <d3d12.h>

namespace tktk
{
	struct TexBuffData
	{
		std::vector<unsigned char>	textureData;
		unsigned int				width;
		unsigned int				height;
	};

	struct TexBufFormatParam
	{
		D3D12_RESOURCE_DIMENSION	resourceDimension;
		DXGI_FORMAT					format;
		unsigned int				arraySize;
		unsigned int				mipLevels;
		unsigned int				sampleDescCount;
		unsigned int				sampleDescQuality;
	};
}
#endif // !TEXTURE_BUFFER_INIT_PARAM_H_