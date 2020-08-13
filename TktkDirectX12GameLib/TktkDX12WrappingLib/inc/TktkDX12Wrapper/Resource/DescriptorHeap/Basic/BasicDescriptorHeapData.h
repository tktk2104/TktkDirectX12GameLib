#ifndef BASIC_DESCRIPTOR_HEAP_DATA_H_
#define BASIC_DESCRIPTOR_HEAP_DATA_H_

#include <vector>
#include "../../../Includer/D3d12Includer.h"
#include "BasicDescriptorHeapInitParam.h"

namespace tktk
{
	// シェーダーリソースビュー、定数バッファビューなど用のディスクリプタヒープクラス
	class BasicDescriptorHeapData
	{
	public:

		BasicDescriptorHeapData(ID3D12Device* device, const BasicDescriptorHeapInitParam& initParam);
		~BasicDescriptorHeapData();

	public:

		// 各ビューのCPUアドレスの配列を取得する
		std::vector<D3D12_CPU_DESCRIPTOR_HANDLE> getCpuHeapHandleArray(ID3D12Device* device) const;

		// ディスクリプタヒープをまとめてコマンドリストに登録するためにあるゲッター
		ID3D12DescriptorHeap* getPtr() const;

		// 各ビューのGPUアドレスをコマンドリストに登録する
		void setRootDescriptorTable(ID3D12Device* device, ID3D12GraphicsCommandList* commandList) const;

	public:

		// それぞれのディスクリプタテーブルが持っているディスクリプタの数の配列
		std::vector<unsigned int> m_descriptorTableSizeArray;

		ID3D12DescriptorHeap*	m_descriptorHeap{ nullptr };
	};
}
#endif // !BASIC_DESCRIPTOR_HEAP_DATA_H_