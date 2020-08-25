#ifndef GRAPHICS_PIPE_LINE_H_
#define GRAPHICS_PIPE_LINE_H_

#include <memory>	// std::unique_ptr
#include "../../Includer/D3d12Includer.h"
#include "GraphicsPipeLineInitParamIncluder.h"
#include "GraphicsPipeLineResourceNum.h"

namespace tktk
{
	// 前方宣言達
	class RootSignature;
	class PipeLineState;

	// グラフィックパイプラインを管理するクラス
	class GraphicsPipeLine
	{
	public:

		explicit GraphicsPipeLine(const GraphicsPipeLineResourceNum& initParam);
		~GraphicsPipeLine();

	public:

		// ルートシグネチャを作る
		unsigned int createRootSignature(ID3D12Device* device, const RootSignatureInitParam& initParam);

	public:

		// パイプラインステートを作る
		unsigned int createPipeLineState(ID3D12Device* device, const PipeLineStateInitParam& initParam, const ShaderFilePaths& shaderFilePath);

	public:

		// グラフィックパイプラインをコマンドリストに登録する
		void set(unsigned int handle, ID3D12GraphicsCommandList* commandList) const;

	private:

		std::unique_ptr<RootSignature> m_rootSignature;
		std::unique_ptr<PipeLineState> m_pipeLineState;
	};
}
#endif // !GRAPHICS_PIPE_LINE_H_