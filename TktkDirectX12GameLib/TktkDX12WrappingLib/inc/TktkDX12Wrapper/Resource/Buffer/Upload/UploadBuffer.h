#ifndef COPY_BUFFER_H_
#define COPY_BUFFER_H_

#include <TktkContainer/ResourceContainer/ResourceContainer.h>
#include "UploadBufferData.h"

namespace tktk
{
	// �uUploadBufferData�v���Ǘ�����N���X
	class UploadBuffer
	{
	public:

		explicit UploadBuffer(const tktkContainer::ResourceContainerInitParam& initParam);
		~UploadBuffer() = default;

	public:

		// �uUploadBufferData�v�̃C���X�^���X�����A���̃��\�[�X�̃n���h����Ԃ�
		size_t create(ID3D12Device* device, const UploadBufferInitParam& initParam);

		// �uUploadBufferData�v�̃C���X�^���X�̃R�s�[�����A���̃��\�[�X�̃n���h����Ԃ�
		size_t duplicate(ID3D12Device* device, size_t originalHandle);

		// �w��̃A�b�v���[�h�o�b�t�@���폜����
		// �������̃n���h���ɑΉ����郊�\�[�X�����������牽�����Ȃ�
		void erase(size_t handle);

		// �����̃|�C���^�̃f�[�^���w��̃A�b�v���[�h�o�b�t�@�ɃR�s�[����
		void updateBuffer(size_t handle, const CopySourceDataCarrier& bufferData);

		// �w��̃A�b�v���[�h�o�b�t�@�̃A�b�v���[�h��̃o�b�t�@�̎�ނ��擾����
		BufferType getTargetBufferType(size_t handle) const;

		// �w��̃A�b�v���[�h�o�b�t�@�̃A�b�v���[�h��̃o�b�t�@�̃n���h�����擾����
		size_t getTargetBufferHandle(size_t handle) const;

		// �����̃o�b�t�@�Ɏw��̃A�b�v���[�h�o�b�t�@�̓��e���A�b�v���[�h����GPU���߂��s��
		void copyBuffer(size_t handle, ID3D12GraphicsCommandList* commandList, ID3D12Resource* targetBuffer) const;

		// �����̃e�N�X�`���o�b�t�@�Ɏw��̃A�b�v���[�h�o�b�t�@�̓��e���A�b�v���[�h����GPU���߂��s��
		void copyTexture(size_t handle, ID3D12GraphicsCommandList* commandList, ID3D12Resource* targetBuffer, const D3D12_TEXTURE_COPY_LOCATION& srcCopyLoaction) const;

	private:

		tktkContainer::ResourceContainer<UploadBufferData> m_uploadBufferDataArray;
	};
}
#endif // !COPY_BUFFER_H_