#ifndef RTV_DESCRIPTOR_HEAP_DATA_H_
#define RTV_DESCRIPTOR_HEAP_DATA_H_

/* std::vector */
#include <vector>

/* ID3D12Device, ID3D12GraphicsCommandList, D3D12_CPU_DESCRIPTOR_HANDLE, ID3D12DescriptorHeap */
#include <d3d12.h>
#undef min
#undef max


#include <TktkMath/Structs/Color.h>
#include "RtvDescriptorHeapInitParam.h"

namespace tktk
{
	// レンダーターゲットビュー用のディスクリプタヒープクラス
	class RtvDescriptorHeapData
	{
	public:

		RtvDescriptorHeapData(ID3D12Device* device, const RtvDescriptorHeapInitParam& initParam);
		~RtvDescriptorHeapData();

		// ムーブコンストラクタ
		RtvDescriptorHeapData(RtvDescriptorHeapData&& other) noexcept;

	public:

		// 各ビューのCPUアドレスの配列を取得する
		std::vector<D3D12_CPU_DESCRIPTOR_HANDLE> getCpuHeapHandleArray(ID3D12Device* device) const;

		// 各ビューが参照しているレンダーターゲットバッファのIDの配列を取得する
		const std::vector<size_t>& getRtBufferHandleArray() const;

		// ディスクリプタヒープをまとめてコマンドリストに登録するためにあるゲッター
		ID3D12DescriptorHeap* getPtr() const;

		// 各ビューのGPUアドレスをコマンドリストに登録する
		void setRootDescriptorTable(ID3D12Device* device, ID3D12GraphicsCommandList* commandList) const;

		// 指定数のレンダーターゲットビューと引数の深度ステンシルビューをコマンドリストに登録する
		void setRtv(ID3D12Device* device, ID3D12GraphicsCommandList* commandList, size_t startRtvLocationIndex, unsigned int rtvCount, const D3D12_CPU_DESCRIPTOR_HANDLE* useDsvHandle) const;

	private:

		std::vector<size_t>			m_rtBufferHandleArray	{};
		ID3D12DescriptorHeap*		m_descriptorHeap		{ nullptr };
	};
}
#endif // !RTV_DESCRIPTOR_HEAP_DATA_H_