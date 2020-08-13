#ifndef ROOT_SIGNATURE_INIT_PARAM_H_
#define ROOT_SIGNATURE_INIT_PARAM_H_

#include <vector>
#include "../../../Includer/D3d12Includer.h"

namespace tktk
{
	struct RootSignatureInitParam
	{
	public:

		struct DescriptorRange
		{
			unsigned int					numDescriptors{};
			D3D12_DESCRIPTOR_RANGE_TYPE		type{};
			unsigned int					startRegisterNum{};
		};

		struct RootParam
		{
			D3D12_SHADER_VISIBILITY			shaderVisibility{};
			std::vector<DescriptorRange>	descriptorTable{};
		};

		struct SamplerDesc
		{
			D3D12_TEXTURE_ADDRESS_MODE	addressU{};
			D3D12_TEXTURE_ADDRESS_MODE	addressV{};
			D3D12_TEXTURE_ADDRESS_MODE	addressW{};
			D3D12_STATIC_BORDER_COLOR	bordercolor{};
			D3D12_FILTER				filter{};
			float						minLod{};
			float						maxLod{};
			D3D12_SHADER_VISIBILITY		shaderVisibility{};
			D3D12_COMPARISON_FUNC		comparisonFunc{};
			unsigned int				shaderRegister{};
		};

	public:

		D3D12_ROOT_SIGNATURE_FLAGS	flag{};
		std::vector<RootParam>		rootParamArray{};
		std::vector<SamplerDesc>	samplerDescArray{};
	};
}
#endif // !ROOT_SIGNATURE_INIT_PARAM_H_