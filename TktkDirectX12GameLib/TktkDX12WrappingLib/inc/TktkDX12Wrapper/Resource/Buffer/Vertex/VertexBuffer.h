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
		size_t create(ID3D12Device* device, size_t strideDataSize, size_t allDataSize);

		// �w��̒��_�o�b�t�@���폜����
		// �������̃n���h���ɑΉ����郊�\�[�X�����������牽�����Ȃ�
		void erase(size_t handle);

		// �R�}���h���X�g�Ɏw��̒��_�o�b�t�@��o�^����
		void set(size_t handle, ID3D12GraphicsCommandList* commandList) const;

		// �R�}���h���X�g�Ɏw��̒��_�o�b�t�@��o�^����i�C���X�^���X�`��p�j
		void set(size_t meshVertHandle, size_t instancingVertHandle, ID3D12GraphicsCommandList* commandList) const;

		// �w��̒��_�o�b�t�@�̃|�C���^���擾����
		ID3D12Resource* getBufferPtr(size_t handle) const;

	private:

		tktkContainer::ResourceContainer<VertexBufferData> m_vertexBufferDataArray;
	};
}
#endif // !VERTEX_BUFFER_H_