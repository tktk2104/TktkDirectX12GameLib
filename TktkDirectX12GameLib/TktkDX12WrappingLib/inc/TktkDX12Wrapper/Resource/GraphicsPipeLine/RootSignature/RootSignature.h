#ifndef ROOT_SIGNATURE_H_
#define ROOT_SIGNATURE_H_

#include <TktkContainer/HeapArray/HeapArray.h>
#include "RootSignatureData.h"

namespace tktk
{
	// 「RootSignatureData」を管理するクラス
	class RootSignature
	{
	public:

		explicit RootSignature(unsigned int rootSignatureNum);
		~RootSignature() = default;

	public:

		// 「RootSignatureData」のインスタンスを作る
		void create(unsigned int id, ID3D12Device* device, const RootSignatureInitParam& initParam);

		// 指定したルートシグネチャのポインタを取得する
		ID3D12RootSignature* getPtr(unsigned int id) const;

		// 指定したルートシグネチャをコマンドリストに登録する
		void set(unsigned int id, ID3D12GraphicsCommandList* commandList) const;

	private:

		tktkContainer::HeapArray<RootSignatureData> m_rootSignatureDataArray;
	};
}
#endif // !ROOT_SIGNATURE_H_