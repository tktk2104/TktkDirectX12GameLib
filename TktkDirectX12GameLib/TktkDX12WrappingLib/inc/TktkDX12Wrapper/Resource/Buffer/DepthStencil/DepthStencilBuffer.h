#ifndef DEPTH_STENCIL_BUFFER_H_
#define DEPTH_STENCIL_BUFFER_H_

#include <TktkContainer/ResourceContainer/ResourceContainer.h>
#include "DepthStencilBufferData.h"

namespace tktk
{
	// �uDepthStencilBufferData�v���Ǘ�����N���X
	class DepthStencilBuffer
	{
	public:

		explicit DepthStencilBuffer(const tktkContainer::ResourceContainerInitParam& initParam);
		~DepthStencilBuffer() = default;

	public:

		// �uDepthStencilBufferData�v�̃C���X�^���X�����A���̃��\�[�X�̃n���h����Ԃ�
		size_t create(ID3D12Device* device, const DepthStencilBufferInitParam& initParam);

		// �w��̐[�x�X�e���V���o�b�t�@���폜����
		// �������̃n���h���ɑΉ����郊�\�[�X�����������牽�����Ȃ�
		void erase(size_t handle);

		// �w��̐[�x�X�e���V���o�b�t�@�̃��\�[�X�o���A��[�x�������ݏ�ԂɕύX����
		// ���V�F�[�_�[���\�[�X�Ƃ��Ďg�p���Ȃ��ݒ�̏ꍇ�ǂ�ł������N���Ȃ�
		void beginWrite(size_t handle, ID3D12GraphicsCommandList* commandList) const;

		// �w��̐[�x�X�e���V���o�b�t�@�̃��\�[�X�o���A���V�F�[�_�[�g�p��ԂɕύX����
		// ���V�F�[�_�[���\�[�X�Ƃ��Ďg�p���Ȃ��ݒ�̏ꍇ�ǂ�ł������N���Ȃ�
		void endWrite(size_t handle, ID3D12GraphicsCommandList* commandList) const;

		// �S�Ă̐[�x�X�e���V���o�b�t�@�̃��\�[�X�o���A��[�x�������ݏ�ԂɕύX����
		// ���V�F�[�_�[���\�[�X�Ƃ��Ďg�p���Ȃ��ݒ�̏ꍇ�ǂ�ł������N���Ȃ�
		void allBeginWrite(ID3D12GraphicsCommandList* commandList) const;

		// �S�Ă̐[�x�X�e���V���o�b�t�@�̃��\�[�X�o���A���V�F�[�_�[�g�p��ԂɕύX����
		// ���V�F�[�_�[���\�[�X�Ƃ��Ďg�p���Ȃ��ݒ�̏ꍇ�ǂ�ł������N���Ȃ�
		void allEndWrite(ID3D12GraphicsCommandList* commandList) const;

		// �w��̐[�x�X�e���V���o�b�t�@���g�p���āA�����̃f�B�X�N���v�^�n���h���ɐ[�x�X�e���V���r���[�����
		void createDsv(size_t handle, ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle) const;

		// �w��̐[�x�X�e���V���o�b�t�@���g�p���āA�����̃f�B�X�N���v�^�n���h���ɃV�F�[�_�[���\�[�X�r���[�����
		// ���V�F�[�_�[���\�[�X�Ƃ��Ďg�p���Ȃ��ݒ�̏ꍇ�A�G���[��f���܂�
		void createSrv(size_t handle, ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle) const;

		// �w��̐[�x�X�e���V���o�b�t�@�摜�̑傫�����擾����i�s�N�Z���j
		const tktkMath::Vector2& getDepthStencilSizePx(size_t handle) const;

		// �w��̐[�x�X�e���V���o�b�t�@�̃|�C���^���擾����
		ID3D12Resource* getBufferPtr(size_t handle) const;

	private:

		tktkContainer::ResourceContainer<DepthStencilBufferData> m_depthStencilBufferDataArray;
	};
}
#endif // !DEPTH_STENCIL_BUFFER_H_
