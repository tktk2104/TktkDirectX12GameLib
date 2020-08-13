#ifndef SHADER_RESOURCE_VIEW_INIT_PARAM_H_
#define SHADER_RESOURCE_VIEW_INIT_PARAM_H_

#include <d3d12.h>

namespace tktk
{
	struct ShaderResourceViewInitParam
	{
		DXGI_FORMAT			format{};
		D3D12_SRV_DIMENSION viewDimension{};
		unsigned int		mostDetailedMip{};
		unsigned int		mipLevels{};
		unsigned int		firstArraySlice{};
		unsigned int		arraySize{};
		unsigned int		planeSlice{};
		float				minLodClamp{};
	};
}
#endif // !SHADER_RESOURCE_VIEW_INIT_PARAM_H_