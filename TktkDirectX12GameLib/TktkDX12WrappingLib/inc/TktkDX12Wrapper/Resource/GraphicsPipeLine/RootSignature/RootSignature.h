#ifndef ROOT_SIGNATURE_H_
#define ROOT_SIGNATURE_H_

#include <TktkContainer/ResourceContainer/ResourceContainer.h>
#include "RootSignatureData.h"

namespace tktk
{
	// 「RootSignatureData」を管理するクラス
	class RootSignature
	{
	public:

		explicit RootSignature(const tktkContainer::ResourceContainerInitParam& initParam);
		~RootSignature() = default;

	public:

		// 「RootSignatureData」のインスタンスを作り、そのリソースのハンドルを返す
		size_t create(ID3D12Device* device, const RootSignatureInitParam& initParam);

		// 指定のルートシグネチャを削除する
		// ※引数のハンドルに対応するリソースが無かったら何もしない
		void erase(size_t handle);

		// 指定したルートシグネチャのポインタを取得する
		ID3D12RootSignature* getPtr(size_t handle) const;

		// 指定したルートシグネチャをコマンドリストに登録する
		void set(size_t handle, ID3D12GraphicsCommandList* commandList) const;

	private:

		tktkContainer::ResourceContainer<RootSignatureData> m_rootSignatureDataArray;
	};
}
#endif // !ROOT_SIGNATURE_H_