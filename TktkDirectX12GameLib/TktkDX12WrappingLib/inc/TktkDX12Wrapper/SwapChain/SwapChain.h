#ifndef SWAP_CHAIN_H_
#define SWAP_CHAIN_H_

#include <dxgi1_6.h>
#include <TktkMath/Structs/Vector2.h>
#include "../Includer/D3d12Includer.h"

namespace tktk
{
	// ダブルバッファリングで使用するスワップチェインを管理するクラス
	class SwapChain
	{
	public:

		SwapChain() = default;
		~SwapChain();

	public:

		// 初期化する
		void initialize(HWND hwnd, IDXGIFactory6* factory, ID3D12CommandQueue* commandQueue, const tktkMath::Vector2& windowSize);

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
