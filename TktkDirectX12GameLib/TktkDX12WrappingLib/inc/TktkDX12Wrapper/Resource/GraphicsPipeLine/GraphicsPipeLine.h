#ifndef GRAPHICS_PIPE_LINE_H_
#define GRAPHICS_PIPE_LINE_H_

/* std::unique_ptr */
#include <memory>

/* ID3D12Device, ID3D12GraphicsCommandList */
#include <d3d12.h>
#undef min
#undef max

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
		size_t createRootSignature(ID3D12Device* device, const RootSignatureInitParam& initParam);

		// 指定のルートシグネチャを削除する
		// ※引数のハンドルに対応するリソースが無かったら何もしない
		void eraseRootSignature(size_t handle);

	public:

		// パイプラインステートを作る
		size_t createPipeLineState(ID3D12Device* device, const PipeLineStateInitParam& initParam, const ShaderFilePaths& shaderFilePath);

		// 指定のパイプラインステートを削除する
		// ※引数のハンドルに対応するリソースが無かったら何もしない
		void erasePipeLineState(size_t handle);

	public:

		// グラフィックパイプラインをコマンドリストに登録する
		void set(size_t handle, ID3D12GraphicsCommandList* commandList) const;

	private:

		std::unique_ptr<RootSignature> m_rootSignature;
		std::unique_ptr<PipeLineState> m_pipeLineState;
	};
}
#endif // !GRAPHICS_PIPE_LINE_H_