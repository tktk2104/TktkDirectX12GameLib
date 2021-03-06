#ifndef DSV_DESCRIPTOR_HEAP_DATA_H_
#define DSV_DESCRIPTOR_HEAP_DATA_H_

/* std::vector */
#include <vector>

/* ID3D12Device, ID3D12GraphicsCommandList, ID3D12DescriptorHeap */
#include <d3d12.h>
#undef min
#undef max

#include <TktkMath/Structs/Color.h>
#include "DsvDescriptorHeapInitParam.h"

namespace tktk
{
	// 深度ステンシルビュー用のディスクリプタヒープクラス
	class DsvDescriptorHeapData
	{
	public:

		DsvDescriptorHeapData(ID3D12Device* device, const DsvDescriptorHeapInitParam& initParam);
		~DsvDescriptorHeapData();

		// ムーブコンストラクタ
		DsvDescriptorHeapData(DsvDescriptorHeapData&& other) noexcept;

	public:

		// 各ビューのCPUアドレスの配列を取得する
		std::vector<D3D12_CPU_DESCRIPTOR_HANDLE> getCpuHeapHandleArray(ID3D12Device* device) const;

		// 各ビューが参照している深度ステンシルバッファのIDの配列を取得する
		const std::vector<size_t>& getDsBufferHandleArray() const;

		// ディスクリプタヒープをまとめてコマンドリストに登録するためにあるゲッター
		ID3D12DescriptorHeap* getPtr() const;

		// 各ビューのGPUアドレスをコマンドリストに登録する
		void setRootDescriptorTable(ID3D12Device* device, ID3D12GraphicsCommandList* commandList) const;

		// レンダーターゲットビューを登録せずに深度ステンシルビューをコマンドリストに登録する
		void setOnlyDsv(ID3D12Device* device, ID3D12GraphicsCommandList* commandList) const;

		// 指定の深度ステンシルビューをクリアする
		void clearDsv(ID3D12Device* device, ID3D12GraphicsCommandList* commandList) const;

	private:

		std::vector<size_t>		m_dsBufferHandleArray	{};
		ID3D12DescriptorHeap*	m_descriptorHeap		{ nullptr };
	};
}
#endif // !DSV_DESCRIPTOR_HEAP_DATA_H_