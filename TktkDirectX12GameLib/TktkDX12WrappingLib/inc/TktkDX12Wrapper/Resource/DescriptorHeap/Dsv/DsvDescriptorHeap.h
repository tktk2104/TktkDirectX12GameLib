#ifndef DSV_DESCRIPTOR_HEAP_H_
#define DSV_DESCRIPTOR_HEAP_H_

#include <TktkContainer/ResourceContainer/ResourceContainer.h>
#include "DsvDescriptorHeapData.h"

namespace tktk
{
	// 「DsvDescriptorHeapData」を管理するクラス
	class DsvDescriptorHeap
	{
	public:

		explicit DsvDescriptorHeap(const tktkContainer::ResourceContainerInitParam& initParam);
		~DsvDescriptorHeap() = default;

	public:

		// 「DsvDescriptorHeapData」のインスタンスを作り、そのリソースのハンドルを返す
		size_t create(ID3D12Device* device, const DsvDescriptorHeapInitParam& initParam);

		// 指定のディスクリプタヒープを削除する
		// ※引数のハンドルに対応するリソースが無かったら何もしない
		void erase(size_t handle);

		// 指定したディスクリプタヒープの各ビューのCPUアドレスの配列を取得する
		std::vector<D3D12_CPU_DESCRIPTOR_HANDLE> getCpuHeapHandleArray(size_t handle, ID3D12Device* device) const;

		// 指定したディスクリプタヒープの各ビューが参照している深度ステンシルバッファのハンドルの配列を取得する
		const std::vector<size_t>& getDsBufferHandleArray(size_t handle) const;

		// 指定したディスクリプタヒープのポインタを取得する
		ID3D12DescriptorHeap* getPtr(size_t handle) const;

		// 指定したディスクリプタヒープの各ビューのGPUアドレスをコマンドリストに登録する
		void setRootDescriptorTable(size_t handle, ID3D12Device* device, ID3D12GraphicsCommandList* commandList) const;

		// レンダーターゲットビューを登録せずに指定したディスクリプタヒープの深度ステンシルビューをコマンドリストに登録する
		void setOnlyDsv(size_t handle, ID3D12Device* device, ID3D12GraphicsCommandList* commandList) const;

		// 深度ステンシルビューを全てクリアする
		void clearDsvAll(ID3D12Device* device, ID3D12GraphicsCommandList* commandList) const;

	private:

		tktkContainer::ResourceContainer<DsvDescriptorHeapData> m_dsvDescriptorHeapDataArray;
	};
}
#endif // !DSV_DESCRIPTOR_HEAP_H_