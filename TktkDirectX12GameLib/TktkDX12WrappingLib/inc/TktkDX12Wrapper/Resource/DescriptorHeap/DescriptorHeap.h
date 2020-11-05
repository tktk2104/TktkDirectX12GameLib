#ifndef DESCRIPTOR_HEAP_H_
#define DESCRIPTOR_HEAP_H_

#include <memory>	// std::unique_ptr
#include <TktkMath/Structs/Color.h>
#include "../../Includer/D3d12Includer.h"
#include "DescriptorHeapInitParamIncluder.h"
#include "DescriptorHeapParam.h"
#include "DescriptorHeapNum.h"

namespace tktk
{
	// 前方宣言達
	class BasicDescriptorHeap;
	class RtvDescriptorHeap;
	class DsvDescriptorHeap;

	// ３種類のディスクリプタヒープを管理するクラス
	class DescriptorHeap
	{
	public:

		explicit DescriptorHeap(const DescriptorHeapNum& initParam);
		~DescriptorHeap();

	public: /* コマンドリストに登録する処理 */

		// 指定のディスクリプタヒープを複数個まとめてコマンドリストに登録する
		void set(ID3D12Device* device, ID3D12GraphicsCommandList* commandList, const std::vector<DescriptorHeapParam>& heapParamArray) const;

	public: /* レンダーターゲット、深度ステンシルをコマンドリストに登録する処理 */

		// レンダーターゲットビューをコマンドリストに登録する
		void setRtv(size_t rtvHandle, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, size_t startRtvLocationIndex, unsigned int rtvCount) const;
		
		// レンダーターゲットビューと深度ステンシルビューをコマンドリストに登録する
		void setRtvAndDsv(size_t rtvHandle, size_t dsvHandle, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, size_t startRtvLocation, unsigned int rtvCount) const;
		
		// レンダーターゲットビューを登録せずに指定したディスクリプタヒープの深度ステンシルビューをコマンドリストに登録する
		void setOnlyDsv(size_t handle, ID3D12Device* device, ID3D12GraphicsCommandList* commandList) const;
		
	public: /* ディスクリプタヒープが持つ各ビューのクリア処理 */
		
		// 指定したレンダーターゲット用のディスクリプタヒープが持つ指定のレンダーターゲットビューをクリアする
		void clearRtv(size_t handle, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, size_t rtvLocationIndex, const tktkMath::Color& color) const;
		
		// 深度ステンシルビューを全てクリアする
		void clearDsvAll(ID3D12Device* device, ID3D12GraphicsCommandList* commandList) const;

	public: /* 作成処理 */

		// 通常のディスクリプタヒープを作る
		size_t createBasicDescriptorHeap(ID3D12Device* device, const BasicDescriptorHeapInitParam& initParam);
		
		// レンダーターゲット用のディスクリプタヒープを作る
		size_t createRtvDescriptorHeap(ID3D12Device* device, const RtvDescriptorHeapInitParam& initParam);
		
		// 深度ステンシル用のディスクリプタヒープを作る
		size_t createDsvDescriptorHeap(ID3D12Device* device, const DsvDescriptorHeapInitParam& initParam);

	public: /* 削除処理 */

		// 指定の通常のディスクリプタヒープを削除する
		// ※引数のハンドルに対応するリソースが無かったら何もしない
		void eraseBasicDescriptorHeap(size_t handle);

		// 指定のレンダーターゲット用のディスクリプタヒープを削除する
		// ※引数のハンドルに対応するリソースが無かったら何もしない
		void eraseRtvDescriptorHeap(size_t handle);

		// 指定の深度ステンシル用のディスクリプタヒープを削除する
		// ※引数のハンドルに対応するリソースが無かったら何もしない
		void eraseDsvDescriptorHeap(size_t handle);

	public: /* CPUハンドルの取得処理 */

		// 指定した通常のディスクリプタヒープの各ビューのCPUアドレスの配列を取得する
		std::vector<D3D12_CPU_DESCRIPTOR_HANDLE> getCpuBasicHeapHandleArray(size_t handle, ID3D12Device* device) const;
		
		// 指定したレンダーターゲット用のディスクリプタヒープの各ビューのCPUアドレスの配列を取得する
		std::vector<D3D12_CPU_DESCRIPTOR_HANDLE> getCpuRtvHeapHandleArray(size_t handle, ID3D12Device* device) const;
		
		// 指定した深度ステンシル用のディスクリプタヒープの各ビューのCPUアドレスの配列を取得する
		std::vector<D3D12_CPU_DESCRIPTOR_HANDLE> getCpuDsvHeapHandleArray(size_t handle, ID3D12Device* device) const;

	public: /* ディスクリプタヒープが持つ各ビューが参照しているバッファのIDを取得する処理 */

		// 指定したレンダーターゲット用のディスクリプタヒープの各ビューが参照しているレンダーターゲットバッファのIDの配列を取得する
		const std::vector<size_t>& getRtvDescriptorHeapUseBufferHandleArray(size_t handle) const;
		
		// 指定した深度ステンシル用のディスクリプタヒープの各ビューが参照している深度ステンシルバッファのIDの配列を取得する
		const std::vector<size_t>& getDsvDescriptorHeapUseBufferHandleArray(size_t handle) const;

	private:

		std::unique_ptr<BasicDescriptorHeap>	m_basicDescriptorHeap;
		std::unique_ptr<RtvDescriptorHeap>		m_rtvDescriptorHeap;
		std::unique_ptr<DsvDescriptorHeap>		m_dsvDescriptorHeap;
	};
}
#endif // !DESCRIPTOR_HEAP_H_