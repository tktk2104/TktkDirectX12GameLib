#ifndef BASIC_DESCRIPTOR_HEAP_H_
#define BASIC_DESCRIPTOR_HEAP_H_

#include <vector>
#include <TktkContainer/ResourceContainer/ResourceContainer.h>
#include "BasicDescriptorHeapData.h"

namespace tktk
{
	// 「BasicDescriptorHeapData」を管理するクラス
	class BasicDescriptorHeap
	{
	public:

		explicit BasicDescriptorHeap(const tktkContainer::ResourceContainerInitParam& initParam);
		~BasicDescriptorHeap() = default;

	public:

		// 「BasicDescriptorHeapData」のインスタンスを作り、そのリソースのハンドルを返す
		size_t create(ID3D12Device* device, const BasicDescriptorHeapInitParam& initParam);

		// 指定のディスクリプタヒープを削除する
		// ※引数のハンドルに対応するリソースが無かったら何もしない
		void erase(size_t handle);

		// 指定したディスクリプタヒープの各ビューのCPUアドレスの配列を取得する
		std::vector<D3D12_CPU_DESCRIPTOR_HANDLE> getCpuHeapHandleArray(size_t handle, ID3D12Device* device) const;

		// 指定したディスクリプタヒープのポインタを取得する
		ID3D12DescriptorHeap* getPtr(size_t handle) const;

		// 指定したディスクリプタヒープの各ビューのGPUアドレスをコマンドリストに登録する
		void setRootDescriptorTable(size_t handle, ID3D12Device* device, ID3D12GraphicsCommandList* commandList) const;

	private:

		tktkContainer::ResourceContainer<BasicDescriptorHeapData> m_basicDescriptorHeapDataArray;
	};
}
#endif // !BASIC_DESCRIPTOR_HEAP_H_