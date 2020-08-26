#ifndef RENDER_TARGET_BUFFER_H_
#define RENDER_TARGET_BUFFER_H_

#include <TktkContainer/ResourceContainer/ResourceContainer.h>
#include "RenderTargetBufferData.h"

namespace tktk
{
	// �uRenderTargetBufferData�v���Ǘ�����N���X
	class RenderTargetBuffer
	{
	public:

		explicit RenderTargetBuffer(const tktkContainer::ResourceContainerInitParam& initParam);
		~RenderTargetBuffer() = default;

	public:

		// �[������uRenderTargetBufferData�v�̃C���X�^���X�����A���̃��\�[�X�̃n���h����Ԃ�
		unsigned int create(ID3D12Device* device, const tktkMath::Vector2& renderTargetSize, const tktkMath::Color& clearColor);

		// �X���b�v�`�F�C������uRenderTargetBufferData�v�̃C���X�^���X�����A���̃��\�[�X�̃n���h����Ԃ�
		unsigned int create(IDXGISwapChain1* swapChain, unsigned int backBufferIndex);

		// �w��̃����_�[�^�[�Q�b�g�o�b�t�@���폜����
		// �������̃n���h���ɑΉ����郊�\�[�X�����������牽�����Ȃ�
		void erase(unsigned int handle);

		// �w��̃����_�[�^�[�Q�b�g�o�b�t�@�̃��\�[�X�o���A�������_�[�^�[�Q�b�g��ԂɕύX����
		void beginWriteBasicRtBuffer(unsigned int handle, ID3D12GraphicsCommandList* commandList) const;

		// �w��̃����_�[�^�[�Q�b�g�o�b�t�@�̃��\�[�X�o���A���V�F�[�_�[�g�p��ԂɕύX����
		void endWriteBasicRtBuffer(unsigned int handle, ID3D12GraphicsCommandList* commandList) const;

		// �w��̃����_�[�^�[�Q�b�g�o�b�t�@�̃��\�[�X�o���A�������_�[�^�[�Q�b�g��ԂɕύX����
		void beginWriteBackBuffer(unsigned int handle, ID3D12GraphicsCommandList* commandList) const;

		// �w��̃����_�[�^�[�Q�b�g�o�b�t�@�̃��\�[�X�o���A���v���Z�b�g��ԂɕύX����
		void endWriteBackBuffer(unsigned int handle, ID3D12GraphicsCommandList* commandList) const;

		// �w��̃����_�[�^�[�Q�b�g�o�b�t�@���g�p���āA�����̃f�B�X�N���v�^�n���h���Ƀ����_�[�^�[�Q�b�g�r���[�����
		void createRtv(unsigned int handle, ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle) const;

		// �w��̃����_�[�^�[�Q�b�g�o�b�t�@���g�p���āA�����̃f�B�X�N���v�^�n���h���ɃV�F�[�_�[���\�[�X�r���[�����
		void createSrv(unsigned int handle, ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle) const;

		// �w��̃����_�[�^�[�Q�b�g�o�b�t�@�摜�̑傫�����擾���i�s�N�Z���j
		const tktkMath::Vector2& getRenderTargetSizePx(unsigned int handle) const;

	private:

		tktkContainer::ResourceContainer<RenderTargetBufferData>	m_renderTargetBufferDataArray;
	};
}
#endif // !RENDER_TARGET_BUFFER_H_