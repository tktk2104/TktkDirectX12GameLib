#ifndef RENDER_TARGET_BUFFER_DATA_H_
#define RENDER_TARGET_BUFFER_DATA_H_

#include <dxgi1_6.h>
#include <TktkMath/Structs/Color.h>
#include <TktkMath/Structs/Vector2.h>
#include "../../../Includer/D3d12Includer.h"

namespace tktk
{
	// �����_�[�^�[�Q�b�g�o�b�t�@���Ǘ�����N���X
	class RenderTargetBufferData
	{
	public:

		// �[������o�b�t�@�����R���X�g���N�^
		RenderTargetBufferData(ID3D12Device* device, const tktkMath::Vector2& renderTargetSize, const tktkMath::Color& clearColor);

		// �X���b�v�`�F�C������o�b�N�o�b�t�@���擾���č��R���X�g���N�^
		RenderTargetBufferData(IDXGISwapChain1* swapChain, unsigned int backBufferIndex);
		~RenderTargetBufferData();

		// ���[�u�R���X�g���N�^
		RenderTargetBufferData(RenderTargetBufferData&& other) noexcept;

	public:

		// �N���A�J���[���擾����
		const tktkMath::Color& getClearColor() const;

		// ���g�̃��\�[�X�o���A�������_�[�^�[�Q�b�g��ԂɕύX����
		void beginWriteBasicRtBuffer(ID3D12GraphicsCommandList* commandList) const;

		// ���g�̃��\�[�X�o���A���V�F�[�_�[�g�p��ԂɕύX����
		void endWriteBasicRtBuffer(ID3D12GraphicsCommandList* commandList) const;

		// ���g�̃��\�[�X�o���A�������_�[�^�[�Q�b�g��ԂɕύX����
		void beginWriteBackBuffer(ID3D12GraphicsCommandList* commandList) const;

		// ���g�̃��\�[�X�o���A���v���Z�b�g��ԂɕύX����
		void endWriteBackBuffer(ID3D12GraphicsCommandList* commandList) const;

		// �����̃f�B�X�N���v�^�n���h���Ƀ����_�[�^�[�Q�b�g�r���[�����
		void createRtv(ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle) const;

		// �����̃f�B�X�N���v�^�n���h���ɃV�F�[�_�[���\�[�X�r���[�����
		void createSrv(ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle) const;

		// �����_�[�^�[�Q�b�g�o�b�t�@�摜�̑傫�����擾����i�s�N�Z���j
		const tktkMath::Vector2& getRenderTargetSizePx() const;

		// ���g�̃o�b�t�@�̃|�C���^���擾����
		ID3D12Resource* getBufferPtr() const;

	private:

		tktkMath::Vector2	m_renderTargetSize;
		tktkMath::Color		m_clearColor;
		ID3D12Resource*		m_renderTargetBuffer	{ nullptr };
		bool				m_mustRelease			{ true };
	};
}
#endif // !RENDER_TARGET_BUFFER_DATA_H_