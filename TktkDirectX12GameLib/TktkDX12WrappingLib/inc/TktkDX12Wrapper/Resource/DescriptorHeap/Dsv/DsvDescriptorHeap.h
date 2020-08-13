#ifndef DSV_DESCRIPTOR_HEAP_H_
#define DSV_DESCRIPTOR_HEAP_H_

#include <TktkContainer/HeapArray/HeapArray.h>
#include "DsvDescriptorHeapData.h"

namespace tktk
{
	// 「DsvDescriptorHeapData」を管理するクラス
	class DsvDescriptorHeap
	{
	public:

		DsvDescriptorHeap(unsigned int dsvDescriptorHeapNum);
		~DsvDescriptorHeap() = default;

	public:

		// 「DsvDescriptorHeapData」のインスタンスを作る
		void create(unsigned int id, ID3D12Device* device, const DsvDescriptorHeapInitParam& initParam);

		// 指定したディスクリプタヒープの各ビューのCPUアドレスの配列を取得する
		std::vector<D3D12_CPU_DESCRIPTOR_HANDLE> getCpuHeapHandleArray(unsigned int id, ID3D12Device* device) const;

		// 指定したディスクリプタヒープの各ビューが参照している深度ステンシルバッファのIDの配列を取得する
		const std::vector<unsigned int>& getDsBufferIdArray(unsigned int id) const;

		// 指定したディスクリプタヒープのポインタを取得する
		ID3D12DescriptorHeap* getPtr(unsigned int id) const;

		// 指定したディスクリプタヒープの各ビューのGPUアドレスをコマンドリストに登録する
		void setRootDescriptorTable(unsigned int id, ID3D12Device* device, ID3D12GraphicsCommandList* commandList) const;

		// レンダーターゲットビューを登録せずに指定したディスクリプタヒープの深度ステンシルビューをコマンドリストに登録する
		void setOnlyDsv(unsigned int id, ID3D12Device* device, ID3D12GraphicsCommandList* commandList) const;

		// 深度ステンシルビューを全てクリアする
		void clearDsvAll(ID3D12Device* device, ID3D12GraphicsCommandList* commandList) const;

	private:

		HeapArray<DsvDescriptorHeapData> m_dsvDescriptorHeapDataArray;
	};
}
#endif // !DSV_DESCRIPTOR_HEAP_H_