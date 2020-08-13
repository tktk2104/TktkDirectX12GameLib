#ifndef CONSTANT_BUFFER_H_
#define CONSTANT_BUFFER_H_

#include <TktkContainer/HeapArray/HeapArray.h>
#include "ConstantBufferData.h"

namespace tktk
{
	// 「ConstantBufferData」を管理するクラス
	class ConstantBuffer
	{
	public:

		ConstantBuffer(unsigned int constantBufferNum);
		~ConstantBuffer() = default;

	public:

		// 「ConstantBufferData」のインスタンスを作る
		void create(unsigned int id, ID3D12Device* device, unsigned int constantBufferTypeSize, const void* constantBufferDataTopPos);
	
		// 指定の定数バッファを使用して、引数のディスクリプタハンドルに定数バッファビューを作る
		void createCbv(unsigned int id, ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle) const;
	
		// 指定の定数バッファを更新する
		// ※アップロードバッファを新規に作成し、そのバッファから自身にコピーする命令をコマンドリストに登録する
		void updateBuffer(unsigned int id, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, unsigned int constantBufferTypeSize, const void* constantBufferDataTopPos);

		// 全てのアップロード用のバッファを削除する
		void deleteUploadBufferAll();

	private:

		HeapArray<ConstantBufferData> m_constantBufferDataArray;
	};
}
#endif // !CONSTANT_BUFFER_H_