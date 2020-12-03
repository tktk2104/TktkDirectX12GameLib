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
	// �_�u���o�b�t�@�����O�Ŏg�p����X���b�v�`�F�C�����Ǘ�����N���X
	class SwapChain
	{
	public:

		SwapChain(HWND hwnd, IDXGIFactory6* factory, ID3D12CommandQueue* commandQueue, const tktkMath::Vector2& windowSize);
		~SwapChain();

	public:

		// ���݂̃o�b�N�o�b�t�@�[�����ʂ���C���f�b�N�X���X�V����
		void updateBackBufferIndex();

		// ��ʂ��t���b�v����
		void flipScreen() const;

		// �o�b�N�o�b�t�@���擾���鏈���ŕK�v�ȃQ�b�^�[
		IDXGISwapChain1* getPtr() const;

		// ���݂̃o�b�N�o�b�t�@�[�����ʂ���C���f�b�N�X���擾����
		unsigned int getCurBackBufferIndex() const;

	private:

		IDXGISwapChain1*	m_swapChain{ nullptr };
		unsigned int		m_curBackBufferIndex{ 0U };
	};
}
#endif // !SWAP_CHAIN_H_
