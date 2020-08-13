#ifndef RENDER_TARGET_BUFFER_DATA_H_
#define RENDER_TARGET_BUFFER_DATA_H_

#include <d3d12.h>
#include <dxgi1_6.h>
#undef min
#undef max
#include <TktkMath/Structs/Color.h>
#include <TktkMath/Structs/Vector2.h>

namespace tktk
{
	// レンダーターゲットバッファを管理するクラス
	class RenderTargetBufferData
	{
	public:

		// ゼロからバッファを作るコンストラクタ
		RenderTargetBufferData(ID3D12Device* device, const tktkMath::Vector2& renderTargetSize, const tktkMath::Color& clearColor);

		// スワップチェインからバックバッファを取得して作るコンストラクタ
		RenderTargetBufferData(IDXGISwapChain1* swapChain, unsigned int backBufferIndex);
		~RenderTargetBufferData();

	public:

		// 自身のリソースバリアをレンダーターゲット状態に変更する
		void beginWriteBasicRtBuffer(ID3D12GraphicsCommandList* commandList) const;

		// 自身のリソースバリアをシェーダー使用状態に変更する
		void endWriteBasicRtBuffer(ID3D12GraphicsCommandList* commandList) const;

		// 自身のリソースバリアをレンダーターゲット状態に変更する
		void beginWriteBackBuffer(ID3D12GraphicsCommandList* commandList) const;

		// 自身のリソースバリアをプリセット状態に変更する
		void endWriteBackBuffer(ID3D12GraphicsCommandList* commandList) const;

		// 引数のディスクリプタハンドルにレンダーターゲットビューを作る
		void createRtv(ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle) const;

		// 引数のディスクリプタハンドルにシェーダーリソースビューを作る
		void createSrv(ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle) const;

		// レンダーターゲットバッファ画像の大きさを取得する（ピクセル）
		const tktkMath::Vector2& getRenderTargetSizePx() const;

	private:

		tktkMath::Vector2	m_renderTargetSize;
		ID3D12Resource*		m_renderTargetBuffer{ nullptr };
		bool				m_mustRelease{ true };
	};
}
#endif // !RENDER_TARGET_BUFFER_DATA_H_