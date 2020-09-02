#ifndef COPY_BUFFER_H_
#define COPY_BUFFER_H_

#include <TktkContainer/ResourceContainer/ResourceContainer.h>
#include "CopyBufferData.h"

namespace tktk
{
	// �uCopyBufferData�v���Ǘ�����N���X
	class CopyBuffer
	{
	public:

		explicit CopyBuffer(const tktkContainer::ResourceContainerInitParam& initParam);
		~CopyBuffer() = default;

	public:

		// �uCopyBufferData�v�̃C���X�^���X�����A���̃��\�[�X�̃n���h����Ԃ�
		unsigned int create(ID3D12Device* device, const CopyBufferInitParam& initParam);

		// �uCopyBufferData�v�̃C���X�^���X�̃R�s�[�����A���̃��\�[�X�̃n���h����Ԃ�
		unsigned int copy(ID3D12Device* device, unsigned int originalHandle);

		// �w��̃R�s�[�o�b�t�@���폜����
		// �������̃n���h���ɑΉ����郊�\�[�X�����������牽�����Ȃ�
		void erase(unsigned int handle);

		// �����̃|�C���^�̃f�[�^���w��̃R�s�[�o�b�t�@�ɃR�s�[����
		void updateBuffer(unsigned int handle, unsigned int bufferSize, const void* bufferDataTopPos);

		// �w��̃R�s�[�o�b�t�@�̃R�s�[��̃o�b�t�@�̎�ނ��擾����
		BufferType getTargetBufferType(unsigned int handle) const;

		// �w��̃R�s�[�o�b�t�@�̃R�s�[��̃o�b�t�@�̃n���h�����擾����
		unsigned int getTargetBufferHandle(unsigned int handle) const;

		// �����̃o�b�t�@�Ɏw��̃R�s�[�o�b�t�@�̓��e���R�s�[����GPU���߂�ݒ肷��
		void copyBuffer(unsigned int handle, ID3D12GraphicsCommandList* commandList, ID3D12Resource* targetBuffer) const;

	private:

		tktkContainer::ResourceContainer<CopyBufferData> m_copyBufferDataArray;
	};
}
#endif // !COPY_BUFFER_H_