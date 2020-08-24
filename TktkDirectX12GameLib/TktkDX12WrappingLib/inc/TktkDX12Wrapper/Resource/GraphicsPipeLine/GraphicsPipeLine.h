#ifndef GRAPHICS_PIPE_LINE_H_
#define GRAPHICS_PIPE_LINE_H_

#include <memory>	// std::unique_ptr
#include "../../Includer/D3d12Includer.h"
#include "GraphicsPipeLineInitParamIncluder.h"

namespace tktk
{
	// 前方宣言達
	class RootSignature;
	class PipeLineState;

	// グラフィックパイプラインを管理するクラス
	class GraphicsPipeLine
	{
	public:

		GraphicsPipeLine(unsigned int pipeLineNum, unsigned int rootSignatureNum);
		~GraphicsPipeLine();

	public:

		// ルートシグネチャを作る
		void createRootSignature(unsigned int id, ID3D12Device* device, const RootSignatureInitParam& initParam);

	public:

		// パイプラインステートを作る
		void createPipeLineState(unsigned int id, ID3D12Device* device, const PipeLineStateInitParam& initParam, const ShaderFilePaths& shaderFilePath);

	public:

		// グラフィックパイプラインをコマンドリストに登録する
		void set(unsigned int id, ID3D12GraphicsCommandList* commandList) const;

	private:

		std::unique_ptr<RootSignature> m_rootSignature;
		std::unique_ptr<PipeLineState> m_pipeLineState;
	};
}
#endif // !GRAPHICS_PIPE_LINE_H_