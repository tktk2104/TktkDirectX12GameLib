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
		unsigned int create(ID3D12Device* device, const DsvDescriptorHeapInitParam& initParam);

		// 指定したディスクリプタヒープの各ビューのCPUアドレスの配列を取得する
		std::vector<D3D12_CPU_DESCRIPTOR_HANDLE> getCpuHeapHandleArray(unsigned int handle, ID3D12Device* device) const;

		// 指定したディスクリプタヒープの各ビューが参照している深度ステンシルバッファのIDの配列を取得する
		const std::vector<unsigned int>& getDsBufferIdArray(unsigned int handle) const;

		// 指定したディスクリプタヒープのポインタを取得する
		ID3D12DescriptorHeap* getPtr(unsigned int handle) const;

		// 指定したディスクリプタヒープの各ビューのGPUアドレスをコマンドリストに登録する
		void setRootDescriptorTable(unsigned int handle, ID3D12Device* device, ID3D12GraphicsCommandList* commandList) const;

		// レンダーターゲットビューを登録せずに指定したディスクリプタヒープの深度ステンシルビューをコマンドリストに登録する
		void setOnlyDsv(unsigned int handle, ID3D12Device* device, ID3D12GraphicsCommandList* commandList) const;

		// 深度ステンシルビューを全てクリアする
		void clearDsvAll(ID3D12Device* device, ID3D12GraphicsCommandList* commandList) const;

	private:

		tktkContainer::ResourceContainer<DsvDescriptorHeapData> m_dsvDescriptorHeapDataArray;
	};
}
#endif // !DSV_DESCRIPTOR_HEAP_H_