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
		size_t create(ID3D12Device* device, const PipeLineStateInitParam& initParam, const ShaderFilePaths& shaderFilePath, ID3D12RootSignature* rootSignaturePtr);

		// 指定のパイプラインステートを削除する
		// ※引数のハンドルに対応するリソースが無かったら何もしない
		void erase(size_t handle);

		// 指定したパイプラインステートが使用しているルートシグネチャのハンドルを取得する
		size_t getUseRootSignatureIndex(size_t handle) const;

		// 指定したパイプラインステートをコマンドリストに登録する
		void set(size_t handle, ID3D12GraphicsCommandList* commandList) const;

	private:

		tktkContainer::ResourceContainer<PipeLineStateData> m_pipeLineStateDataArray;
	};
}
#endif // !GRAPHICS_PIPELINE_STATE_H_