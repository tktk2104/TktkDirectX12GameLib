#ifndef ROOT_SIGNATURE_INIT_PARAM_H_
#define ROOT_SIGNATURE_INIT_PARAM_H_

#include <vector>

/*  */
#include <d3d12.h>
#undef min
#undef max

namespace tktk
{
	// ルートシグネチャを作る時に必要な変数
	struct RootSignatureInitParam
	{
	public:

		// ディスクリプタレンジを作る時に必要な変数
		struct DescriptorRange
		{
			unsigned int					numDescriptors	{};
			D3D12_DESCRIPTOR_RANGE_TYPE		type			{};
			unsigned int					startRegisterNum{};
		};

		// ルートパラメーターを作る時に必要な変数
		struct RootParam
		{
			D3D12_SHADER_VISIBILITY			shaderVisibility{};
			std::vector<DescriptorRange>	descriptorTable	{};
		};

		// サンプラーデスクを作る時に必要な情報
		struct SamplerDesc
		{
			D3D12_TEXTURE_ADDRESS_MODE	addressU		{};
			D3D12_TEXTURE_ADDRESS_MODE	addressV		{};
			D3D12_TEXTURE_ADDRESS_MODE	addressW		{};
			D3D12_STATIC_BORDER_COLOR	bordercolor		{};
			D3D12_FILTER				filter			{};
			float						minLod			{};
			float						maxLod			{};
			D3D12_SHADER_VISIBILITY		shaderVisibility{};
			D3D12_COMPARISON_FUNC		comparisonFunc	{};
			unsigned int				shaderRegister	{};
		};

	public:

		D3D12_ROOT_SIGNATURE_FLAGS	flag				{};
		std::vector<RootParam>		rootParamArray		{};
		std::vector<SamplerDesc>	samplerDescArray	{};
	};
}
#endif // !ROOT_SIGNATURE_INIT_PARAM_H_