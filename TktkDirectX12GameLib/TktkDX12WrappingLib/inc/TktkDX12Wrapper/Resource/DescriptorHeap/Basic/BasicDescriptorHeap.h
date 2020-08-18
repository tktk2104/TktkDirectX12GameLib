#ifndef BASIC_DESCRIPTOR_HEAP_H_
#define BASIC_DESCRIPTOR_HEAP_H_

#include <vector>
#include <TktkContainer/HeapArray/HeapArray.h>
#include "BasicDescriptorHeapData.h"

namespace tktk
{
	// 「BasicDescriptorHeapData」を管理するクラス
	class BasicDescriptorHeap
	{
	public:

		explicit BasicDescriptorHeap(unsigned int basicDescriptorHeapNum);
		~BasicDescriptorHeap() = default;

	public:

		// 「BasicDescriptorHeapData」のインスタンスを作る
		void create(unsigned int id, ID3D12Device* device, const BasicDescriptorHeapInitParam& initParam);

		// 指定したディスクリプタヒープの各ビューのCPUアドレスの配列を取得する
		std::vector<D3D12_CPU_DESCRIPTOR_HANDLE> getCpuHeapHandleArray(unsigned int id, ID3D12Device* device) const;

		// 指定したディスクリプタヒープのポインタを取得する
		ID3D12DescriptorHeap* getPtr(unsigned int id) const;

		// 指定したディスクリプタヒープの各ビューのGPUアドレスをコマンドリストに登録する
		void setRootDescriptorTable(unsigned int id, ID3D12Device* device, ID3D12GraphicsCommandList* commandList) const;

	private:

		tktkContainer::HeapArray<BasicDescriptorHeapData> m_basicDescriptorHeapDataArray;
	};
}
#endif // !BASIC_DESCRIPTOR_HEAP_H_