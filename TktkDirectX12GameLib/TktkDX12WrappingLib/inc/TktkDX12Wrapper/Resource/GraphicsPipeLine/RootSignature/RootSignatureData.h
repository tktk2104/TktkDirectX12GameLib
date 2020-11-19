#ifndef ROOT_SIGNATURE_DATA_H_
#define ROOT_SIGNATURE_DATA_H_

/* ID3D12Device, ID3D12GraphicsCommandList, ID3D12RootSignature */
#include <d3d12.h>
#undef min
#undef max

#include "RootSignatureInitParam.h"

namespace tktk
{
	// ルートシグネチャを管理するクラス
	class RootSignatureData
	{
	public:

		RootSignatureData(ID3D12Device* device, const RootSignatureInitParam& initParam);
		~RootSignatureData();

		// ムーブコンストラクタ
		RootSignatureData(RootSignatureData&& other) noexcept;

	public:

		// パイプラインステートを作るためにあるゲッター
		ID3D12RootSignature* getPtr() const;

		// 自身をコマンドリストに登録する
		void set(ID3D12GraphicsCommandList* commandList) const;

	private:

		ID3D12RootSignature* m_rootSignature{ nullptr };
	};
}
#endif // !ROOT_SIGNATURE_DATA_H_