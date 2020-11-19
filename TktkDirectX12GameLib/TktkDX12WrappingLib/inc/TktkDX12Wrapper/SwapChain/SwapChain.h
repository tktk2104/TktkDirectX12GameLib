#ifndef SWAP_CHAIN_H_
#define SWAP_CHAIN_H_

/* IDXGIFactory6, IDXGISwapChain1 */
#include <dxgi1_6.h>

/* ID3D12CommandQueue */
#include <d3d12.h>
#undef min
#undef max

#include <TktkMath/Structs/Vector2.h>

namespace tktk
{
	// ダブルバッファリングで使用するスワップチェインを管理するクラス
	class SwapChain
	{
	public:

		SwapChain(HWND hwnd, IDXGIFactory6* factory, ID3D12CommandQueue* commandQueue, const tktkMath::Vector2& windowSize);
		~SwapChain();

	public:

		// 現在のバックバッファーを識別するインデックスを更新する
		void updateBackBufferIndex();

		// 画面をフリップする
		void flipScreen() const;

		// バックバッファを取得する処理で必要なゲッター
		IDXGISwapChain1* getPtr() const;

		// 現在のバックバッファーを識別するインデックスを取得する
		unsigned int getCurBackBufferIndex() const;

	private:

		IDXGISwapChain1*	m_swapChain{ nullptr };
		unsigned int		m_curBackBufferIndex{ 0U };
	};
}
#endif // !SWAP_CHAIN_H_
