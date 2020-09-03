#ifndef CONSTANT_BUFFER_H_
#define CONSTANT_BUFFER_H_

#include <TktkContainer/ResourceContainer/ResourceContainer.h>
#include "ConstantBufferData.h"

namespace tktk
{
	// 「ConstantBufferData」を管理するクラス
	class ConstantBuffer
	{
	public:

		explicit ConstantBuffer(const tktkContainer::ResourceContainerInitParam& initParam);
		~ConstantBuffer() = default;

	public:

		// 「ConstantBufferData」のインスタンスを作り、そのリソースのハンドルを返す
		unsigned int create(ID3D12Device* device, unsigned int constantBufferTypeSize, const void* constantBufferDataTopPos);

		// 指定の定数バッファを削除する
		// ※引数のハンドルに対応するリソースが無かったら何もしない
		void erase(unsigned int handle);
	
		// 指定の定数バッファを使用して、引数のディスクリプタハンドルに定数バッファビューを作る
		void createCbv(unsigned int handle, ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle) const;

		// 指定の定数バッファのポインタを取得する
		ID3D12Resource* getBufferPtr(unsigned int handle) const;

	private:

		tktkContainer::ResourceContainer<ConstantBufferData> m_constantBufferDataArray;
	};
}
#endif // !CONSTANT_BUFFER_H_