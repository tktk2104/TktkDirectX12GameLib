#ifndef PIPELINE_STATE_DATA_H_
#define PIPELINE_STATE_DATA_H_

#include <d3d12.h>
#include "PipeLineStateInitParam.h"

namespace tktk
{
	// パイプラインステートを管理するクラス
	class PipeLineStateData
	{
	public:

		PipeLineStateData(
			ID3D12Device* device,
			const PipeLineStateInitParam& initParam,
			const std::vector<char>& vsByteArray,
			const std::vector<char>& psByteArray,
			ID3D12RootSignature* rootSignaturePtr
		);
		~PipeLineStateData();

	public:

		// 使用しているルートシグネチャのIDを取得する
		unsigned int getUseRootSignatureIndex() const;

		// 自身をコマンドリストに登録する
		void set(ID3D12GraphicsCommandList* commandList) const;

	private:

		int						m_rootSignatureId{};
		ID3D12PipelineState*	m_pipeLineState{ nullptr };
	};
}
#endif // !PIPELINE_STATE_DATA_H_