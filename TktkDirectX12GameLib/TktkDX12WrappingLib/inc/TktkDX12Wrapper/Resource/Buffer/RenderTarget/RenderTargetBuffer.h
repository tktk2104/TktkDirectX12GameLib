#ifndef RENDER_TARGET_BUFFER_H_
#define RENDER_TARGET_BUFFER_H_

#include <TktkContainer/HeapArray/HeapArray.h>
#include "RenderTargetBufferData.h"

namespace tktk
{
	// 「RenderTargetBufferData」を管理するクラス
	class RenderTargetBuffer
	{
	public:

		RenderTargetBuffer(unsigned int renderTargetBufferNum);
		~RenderTargetBuffer() = default;

	public:

		// ゼロから「RenderTargetBufferData」のインスタンスを作る
		void create(unsigned int id, ID3D12Device* device, const tktkMath::Vector2& renderTargetSize, const tktkMath::Color& clearColor);

		// スワップチェインから「RenderTargetBufferData」のインスタンスを作る
		void create(unsigned int id, IDXGISwapChain1* swapChain, unsigned int backBufferIndex);

		// 指定のレンダーターゲットバッファのリソースバリアをレンダーターゲット状態に変更する
		void beginWriteBasicRtBuffer(unsigned int id, ID3D12GraphicsCommandList* commandList) const;

		// 指定のレンダーターゲットバッファのリソースバリアをシェーダー使用状態に変更する
		void endWriteBasicRtBuffer(unsigned int id, ID3D12GraphicsCommandList* commandList) const;

		// 指定のレンダーターゲットバッファのリソースバリアをレンダーターゲット状態に変更する
		void beginWriteBackBuffer(unsigned int id, ID3D12GraphicsCommandList* commandList) const;

		// 指定のレンダーターゲットバッファのリソースバリアをプリセット状態に変更する
		void endWriteBackBuffer(unsigned int id, ID3D12GraphicsCommandList* commandList) const;

		// 指定のレンダーターゲットバッファを使用して、引数のディスクリプタハンドルにレンダーターゲットビューを作る
		void createRtv(unsigned int id, ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle) const;

		// 指定のレンダーターゲットバッファを使用して、引数のディスクリプタハンドルにシェーダーリソースビューを作る
		void createSrv(unsigned int id, ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle) const;

		// 指定のレンダーターゲットバッファ画像の大きさを取得す（ピクセル）
		const tktkMath::Vector2& getRenderTargetSizePx(unsigned int id) const;

	private:

		HeapArray<RenderTargetBufferData>	m_renderTargetBufferDataArray;
	};
}
#endif // !RENDER_TARGET_BUFFER_H_