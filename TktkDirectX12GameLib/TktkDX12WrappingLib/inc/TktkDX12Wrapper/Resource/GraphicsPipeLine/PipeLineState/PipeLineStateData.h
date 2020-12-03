#ifndef PIPELINE_STATE_DATA_H_
#define PIPELINE_STATE_DATA_H_

/* ID3D12Device, ID3D12GraphicsCommandList, ID3D12PipelineState, ID3D12RootSignature */
#include <d3d12.h>
#undef min
#undef max

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

		// ムーブコンストラクタ
		PipeLineStateData(PipeLineStateData&& other) noexcept;

	public:

		// 使用しているルートシグネチャのIDを取得する
		size_t getUseRootSignatureHandle() const;

		// 自身をコマンドリストに登録する
		void set(ID3D12GraphicsCommandList* commandList) const;

	private:

		size_t					m_rootSignatureHandle	{};
		ID3D12PipelineState*	m_pipeLineState			{ nullptr };
	};
}
#endif // !PIPELINE_STATE_DATA_H_