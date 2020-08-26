#ifndef RTV_DESCRIPTOR_HEAP_H_
#define RTV_DESCRIPTOR_HEAP_H_

#include <vector>
#include <TktkContainer/ResourceContainer/ResourceContainer.h>
#include "RtvDescriptorHeapData.h"

namespace tktk
{
	// 「RtvDescriptorHeapData」を管理するクラス
	class RtvDescriptorHeap
	{
	public:

		explicit RtvDescriptorHeap(const tktkContainer::ResourceContainerInitParam& initParam);
		~RtvDescriptorHeap() = default;

	public:

		// 「RtvDescriptorHeapData」のインスタンスを作り、そのリソースのハンドルを返す
		unsigned int create(ID3D12Device* device, const RtvDescriptorHeapInitParam& initParam);

		// 指定のディスクリプタヒープを削除する
		// ※引数のハンドルに対応するリソースが無かったら何もしない
		void erase(unsigned int handle);

		// 指定したディスクリプタヒープの各ビューのCPUアドレスの配列を取得する
		std::vector<D3D12_CPU_DESCRIPTOR_HANDLE> getCpuHeapHandleArray(unsigned int handle, ID3D12Device* device) const;

		// 指定したディスクリプタヒープの各ビューが参照しているレンダーターゲットバッファのIDの配列を取得する
		const std::vector<unsigned int>& getRtBufferIdArray(unsigned int handle) const;

		// 指定したディスクリプタヒープのポインタを取得する
		ID3D12DescriptorHeap* getPtr(unsigned int handle) const;

		// 指定したディスクリプタヒープの各ビューのGPUアドレスをコマンドリストに登録する
		void setRootDescriptorTable(unsigned int handle, ID3D12Device* device, ID3D12GraphicsCommandList* commandList) const;
	
		// 指定したディスクリプタヒープの指定数のレンダーターゲットビューと引数の深度ステンシルビューをコマンドリストに登録する
		void setRtv(unsigned int handle, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, unsigned int startRtvLocationIndex, unsigned int rtvCount, const D3D12_CPU_DESCRIPTOR_HANDLE* useDsvHandle) const;

		// 指定したディスクリプタヒープが持つ指定のレンダーターゲットビューをクリアする
		void clearRtv(unsigned int handle, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, unsigned int rtvLocationIndex, const tktkMath::Color& color) const;

	private:

		tktkContainer::ResourceContainer<RtvDescriptorHeapData> m_rtvDescriptorHeapDataArray;
	};
}
#endif // !RTV_DESCRIPTOR_HEAP_H_