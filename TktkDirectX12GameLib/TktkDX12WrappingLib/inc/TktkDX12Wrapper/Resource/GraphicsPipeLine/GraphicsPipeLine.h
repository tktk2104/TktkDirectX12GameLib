#ifndef GRAPHICS_PIPE_LINE_H_
#define GRAPHICS_PIPE_LINE_H_

#include "PipeLineState/PipeLineState.h"
#include "RootSignature/RootSignature.h"

namespace tktk
{
	// グラフィックパイプラインを管理するクラス
	class GraphicsPipeLine
	{
	public:

		GraphicsPipeLine(unsigned int pipeLineNum, unsigned int rootSignatureNum);

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

		RootSignature m_rootSignature;
		PipeLineState m_pipeLineState;
	};
}
#endif // !GRAPHICS_PIPE_LINE_H_
