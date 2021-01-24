#ifndef INDEX_BUFFER_H_
#define INDEX_BUFFER_H_

#include <TktkContainer/ResourceContainer/ResourceContainer.h>
#include "IndexBufferData.h"

namespace tktk
{
	// �uIndexBufferData�v���Ǘ�����N���X
	class IndexBuffer
	{
	public:

		explicit IndexBuffer(const tktkContainer::ResourceContainerInitParam& initParam);
		~IndexBuffer() = default;

	public:

		// �uIndexBufferData�v�̃C���X�^���X�����A���̃��\�[�X�̃n���h����Ԃ�
		size_t create(ID3D12Device* device, size_t dataSize);

		// �w��̃C���f�b�N�X�o�b�t�@���폜����
		// �������̃n���h���ɑΉ����郊�\�[�X�����������牽�����Ȃ�
		void erase(size_t handle);

		// �R�}���h���X�g�Ɏw��̃C���f�b�N�X�o�b�t�@��o�^����
		void set(size_t handle, ID3D12GraphicsCommandList* commandList) const;

		// �w��̃C���f�b�N�X�o�b�t�@�̃|�C���^���擾����
		ID3D12Resource* getBufferPtr(size_t handle) const;

	private:

		tktkContainer::ResourceContainer<IndexBufferData> m_indexBufferDataArray;
	};
}
#endif // !INDEX_BUFFER_H_