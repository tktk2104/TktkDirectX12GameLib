#ifndef GRAPHICS_PIPELINE_STATE_H_
#define GRAPHICS_PIPELINE_STATE_H_

#include <TktkContainer/ResourceContainer/ResourceContainer.h>
#include "PipeLineStateData.h"

namespace tktk
{
	// 「PipeLineStateData」を管理するクラス
	class PipeLineState
	{
	public:

		explicit PipeLineState(const tktkContainer::ResourceContainerInitParam& initParam);
		~PipeLineState() = default;

	public:

		// 「PipeLineStateData」のインスタンスを作り、そのリソースのハンドルを返す
		unsigned int create(ID3D12Device* device, const PipeLineStateInitParam& initParam, const ShaderFilePaths& shaderFilePath, ID3D12RootSignature* rootSignaturePtr);

		// 指定のパイプラインステートを削除する
		// ※引数のハンドルに対応するリソースが無かったら何もしない
		void erase(unsigned int handle);

		// 指定したパイプラインステートが使用しているルートシグネチャのハンドルを取得する
		unsigned int getUseRootSignatureIndex(unsigned int handle) const;

		// 指定したパイプラインステートをコマンドリストに登録する
		void set(unsigned int handle, ID3D12GraphicsCommandList* commandList) const;

	private:

		tktkContainer::ResourceContainer<PipeLineStateData> m_pipeLineStateDataArray;
	};
}
#endif // !GRAPHICS_PIPELINE_STATE_H_