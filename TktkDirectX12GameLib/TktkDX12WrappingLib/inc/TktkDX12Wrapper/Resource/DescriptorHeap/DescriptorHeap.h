#ifndef DESCRIPTOR_HEAP_H_
#define DESCRIPTOR_HEAP_H_

#include "DescriptorHeapNum.h"
#include "DescriptorHeapParam.h"

#include "Basic/BasicDescriptorHeap.h"
#include "Rtv/RtvDescriptorHeap.h"
#include "Dsv/DsvDescriptorHeap.h"

namespace tktk
{
	// ３種類のディスクリプタヒープを管理するクラス
	class DescriptorHeap
	{
	public:

		DescriptorHeap(const DescriptorHeapNum& initParam);

	public: /* コマンドリストに登録する処理 */

		// 指定のディスクリプタヒープを複数個まとめてコマンドリストに登録する
		void set(ID3D12Device* device, ID3D12GraphicsCommandList* commandList, const std::vector<DescriptorHeapParam>& heapParamArray) const;

	public: /* レンダーターゲット、深度ステンシルをコマンドリストに登録する処理 */

		// レンダーターゲットビューをコマンドリストに登録する
		void setRtv(unsigned int rtvDescriptorHeapId, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, unsigned int startRtvLocationIndex, unsigned int rtvCount) const;
		
		// レンダーターゲットビューと深度ステンシルビューをコマンドリストに登録する
		void setRtvAndDsv(unsigned int renderTargetId, unsigned int depthStencilViewId, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, unsigned int startRtvLocation, unsigned int rtvCount) const;
		
		// レンダーターゲットビューを登録せずに指定したディスクリプタヒープの深度ステンシルビューをコマンドリストに登録する
		void setOnlyDsv(unsigned int id, ID3D12Device* device, ID3D12GraphicsCommandList* commandList) const;
		
	public: /* ディスクリプタヒープが持つ各ビューのクリア処理 */
		
		// 指定したレンダーターゲット用のディスクリプタヒープが持つ指定のレンダーターゲットビューをクリアする
		void clearRtv(unsigned int id, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, unsigned int rtvLocationIndex, const tktkMath::Color& color) const;
		
		// 深度ステンシルビューを全てクリアする
		void clearDsvAll(ID3D12Device* device, ID3D12GraphicsCommandList* commandList) const;

	public: /* 作成処理 */

		// 通常のディスクリプタヒープを作る
		void createBasicDescriptorHeap(unsigned int id, ID3D12Device* device, const BasicDescriptorHeapInitParam& initParam);
		
		// レンダーターゲット用のディスクリプタヒープを作る
		void createRtvDescriptorHeap(unsigned int id, ID3D12Device* device, const RtvDescriptorHeapInitParam& initParam);
		
		// 深度ステンシル用のディスクリプタヒープを作る
		void createDsvDescriptorHeap(unsigned int id, ID3D12Device* device, const DsvDescriptorHeapInitParam& initParam);

	public: /* CPUハンドルの取得処理 */

		// 指定した通常のディスクリプタヒープの各ビューのCPUアドレスの配列を取得する
		std::vector<D3D12_CPU_DESCRIPTOR_HANDLE> getCpuBasicHeapHandleArray(unsigned int id, ID3D12Device* device) const;
		
		// 指定したレンダーターゲット用のディスクリプタヒープの各ビューのCPUアドレスの配列を取得する
		std::vector<D3D12_CPU_DESCRIPTOR_HANDLE> getCpuRtvHeapHandleArray(unsigned int id, ID3D12Device* device) const;
		
		// 指定した深度ステンシル用のディスクリプタヒープの各ビューのCPUアドレスの配列を取得する
		std::vector<D3D12_CPU_DESCRIPTOR_HANDLE> getCpuDsvHeapHandleArray(unsigned int id, ID3D12Device* device) const;

	public: /* ディスクリプタヒープが持つ各ビューが参照しているバッファのIDを取得する処理 */

		// 指定したレンダーターゲット用のディスクリプタヒープの各ビューが参照しているレンダーターゲットバッファのIDの配列を取得する
		const std::vector<unsigned int>& getRtvDescriptorHeapUseBufferIdArray(unsigned int id) const;
		
		// 指定した深度ステンシル用のディスクリプタヒープの各ビューが参照している深度ステンシルバッファのIDの配列を取得する
		const std::vector<unsigned int>& getDsvDescriptorHeapUseBufferIdArray(unsigned int id) const;

	private:

		BasicDescriptorHeap	m_basicDescriptorHeap;
		RtvDescriptorHeap	m_rtvDescriptorHeap;
		DsvDescriptorHeap	m_dsvDescriptorHeap;
	};
}
#endif // !DESCRIPTOR_HEAP_H_