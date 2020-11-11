#ifndef RENDER_TARGET_BUFFER_H_
#define RENDER_TARGET_BUFFER_H_

#include <TktkContainer/ResourceContainer/ResourceContainer.h>
#include "RenderTargetBufferData.h"

namespace tktk
{
	// 「RenderTargetBufferData」を管理するクラス
	class RenderTargetBuffer
	{
	public:

		explicit RenderTargetBuffer(const tktkContainer::ResourceContainerInitParam& initParam);
		~RenderTargetBuffer() = default;

	public:

		// ゼロから「RenderTargetBufferData」のインスタンスを作り、そのリソースのハンドルを返す
		size_t create(ID3D12Device* device, const tktkMath::Vector2& renderTargetSize, const tktkMath::Color& clearColor);

		// スワップチェインから「RenderTargetBufferData」のインスタンスを作り、そのリソースのハンドルを返す
		size_t create(IDXGISwapChain1* swapChain, unsigned int backBufferIndex);

		// 指定のレンダーターゲットバッファを削除する
		// ※引数のハンドルに対応するリソースが無かったら何もしない
		void erase(size_t handle);

		// 指定のレンダーターゲットバッファのクリアカラーを取得する
		const tktkMath::Color& getClearColor(size_t handle) const;

		// 指定のレンダーターゲットバッファのリソースバリアをレンダーターゲット状態に変更する
		void beginWriteBasicRtBuffer(size_t handle, ID3D12GraphicsCommandList* commandList) const;

		// 指定のレンダーターゲットバッファのリソースバリアをシェーダー使用状態に変更する
		void endWriteBasicRtBuffer(size_t handle, ID3D12GraphicsCommandList* commandList) const;

		// 指定のレンダーターゲットバッファのリソースバリアをレンダーターゲット状態に変更する
		void beginWriteBackBuffer(size_t handle, ID3D12GraphicsCommandList* commandList) const;

		// 指定のレンダーターゲットバッファのリソースバリアをプリセット状態に変更する
		void endWriteBackBuffer(size_t handle, ID3D12GraphicsCommandList* commandList) const;

		// 指定のレンダーターゲットバッファを使用して、引数のディスクリプタハンドルにレンダーターゲットビューを作る
		void createRtv(size_t handle, ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle) const;

		// 指定のレンダーターゲットバッファを使用して、引数のディスクリプタハンドルにシェーダーリソースビューを作る
		void createSrv(size_t handle, ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle) const;

		// 指定のレンダーターゲットバッファ画像の大きさを取得す（ピクセル）
		const tktkMath::Vector2& getRenderTargetSizePx(size_t handle) const;

		// 指定のレンダーターゲットバッファのポインタを取得する
		ID3D12Resource* getBufferPtr(size_t handle) const;

	private:

		tktkContainer::ResourceContainer<RenderTargetBufferData>	m_renderTargetBufferDataArray;
	};
}
#endif // !RENDER_TARGET_BUFFER_H_