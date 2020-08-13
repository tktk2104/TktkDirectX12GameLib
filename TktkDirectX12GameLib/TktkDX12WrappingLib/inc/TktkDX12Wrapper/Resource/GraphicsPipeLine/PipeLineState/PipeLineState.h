#ifndef GRAPHICS_PIPELINE_STATE_H_
#define GRAPHICS_PIPELINE_STATE_H_

#include <string>
#include <TktkContainer/HeapArray/HeapArray.h>
#include "PipeLineStateData.h"

namespace tktk
{
	// 「PipeLineStateData」を管理するクラス
	class PipeLineState
	{
	public:

		PipeLineState(unsigned int pipeLineNum);
		~PipeLineState() = default;

	public:

		// 「PipeLineStateData」のインスタンスを作る
		void createPipeLineState(unsigned int id, ID3D12Device* device, const PipeLineStateInitParam& initParam, const ShaderFilePaths& shaderFilePath, ID3D12RootSignature* rootSignaturePtr);

		// 指定したパイプラインステートが使用しているルートシグネチャのIDを取得する
		unsigned int getUseRootSignatureIndex(unsigned int id) const;

		// 指定したパイプラインステートをコマンドリストに登録する
		void set(unsigned int id, ID3D12GraphicsCommandList* commandList) const;

	private:

		HeapArray<PipeLineStateData> m_pipeLineStateDataArray;
	};
}
#endif // !GRAPHICS_PIPELINE_STATE_H_