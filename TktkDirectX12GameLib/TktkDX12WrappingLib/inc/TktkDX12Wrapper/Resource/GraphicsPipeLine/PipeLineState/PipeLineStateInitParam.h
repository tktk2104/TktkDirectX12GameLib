#ifndef PIPELINE_STATE_INIT_PARAM_H_
#define PIPELINE_STATE_INIT_PARAM_H_

#include <string>
#include <vector>
#include "../../../Includer/D3d12Includer.h"

namespace tktk
{
	// パイプランスステートを作る時に必要な変数
	struct PipeLineStateInitParam
	{
		D3D12_RASTERIZER_DESC					rasterizerDesc			{};
		D3D12_BLEND_DESC						blendDesc				{};
		unsigned int							sampleMask				{ D3D12_DEFAULT_SAMPLE_MASK };
		std::vector<D3D12_INPUT_ELEMENT_DESC>	inputLayoutArray		{};
		D3D12_PRIMITIVE_TOPOLOGY_TYPE			primitiveTopology		{};
		std::vector<DXGI_FORMAT>				renderTargetFormatArray	{};
		bool									useDepth				{ false };
		bool									writeDepth				{ false };
		D3D12_COMPARISON_FUNC					depthFunc				{};
		size_t									rootSignatureHandle		{ 0 };
	};

	// シェーダーのファイルパス
	struct ShaderFilePaths
	{
		std::string vsFilePath;
		std::string psFilePath;
	};
}
#endif // !PIPELINE_STATE_INIT_PARAM_H_