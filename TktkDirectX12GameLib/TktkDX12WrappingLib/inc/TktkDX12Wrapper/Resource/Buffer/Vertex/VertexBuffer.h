#ifndef VERTEX_BUFFER_H_
#define VERTEX_BUFFER_H_

#include <TktkContainer/ResourceContainer/ResourceContainer.h>
#include "VertexBufferData.h"

namespace tktk
{
	// �uVertexBufferData�v���Ǘ�����N���X
	class VertexBuffer
	{
	public:

		explicit VertexBuffer(const tktkContainer::ResourceContainerInitParam& initParam);
		~VertexBuffer() = default;

	public:

		// �uVertexBufferData�v�̃C���X�^���X�����A���̃��\�[�X�̃n���h����Ԃ�
		unsigned int create(ID3D12Device* device, unsigned int vertexTypeSize, unsigned int vertexDataCount, const void* vertexDataTopPos);

		// �w��̒��_�o�b�t�@���폜����
		// �������̃n���h���ɑΉ����郊�\�[�X�����������牽�����Ȃ�
		void erase(unsigned int handle);

		// �R�}���h���X�g�Ɏw��̒��_�o�b�t�@��o�^����
		void set(unsigned int handle, ID3D12GraphicsCommandList* commandList) const;

		// �w��̒��_�o�b�t�@���X�V����
		// ���A�b�v���[�h�o�b�t�@��V�K�ɍ쐬���A���̃o�b�t�@���玩�g�ɃR�s�[���閽�߂��R�}���h���X�g�ɓo�^����
		void updateBuffer(unsigned int handle, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, unsigned int vertexTypeSize, unsigned int vertexDataCount, const void* vertexDataTopPos);

		// �S�ẴA�b�v���[�h�p�̃o�b�t�@���폜����
		void deleteUploadBufferAll();

		// �w��̒��_�o�b�t�@�̃|�C���^���擾����
		ID3D12Resource* getBufferPtr(unsigned int handle) const;

	private:

		tktkContainer::ResourceContainer<VertexBufferData> m_vertexBufferDataArray;
	};
}
#endif // !VERTEX_BUFFER_H_