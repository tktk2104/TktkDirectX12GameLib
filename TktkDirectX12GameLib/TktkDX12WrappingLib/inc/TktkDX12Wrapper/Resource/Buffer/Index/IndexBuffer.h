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
		unsigned int create(ID3D12Device* device, const std::vector<unsigned short>& indexDataArray);

		// �w��̃C���f�b�N�X�o�b�t�@���폜����
		// �������̃n���h���ɑΉ����郊�\�[�X�����������牽�����Ȃ�
		void erase(unsigned int handle);

		// �R�}���h���X�g�Ɏw��̃C���f�b�N�X�o�b�t�@��o�^����
		void set(unsigned int handle, ID3D12GraphicsCommandList* commandList) const;

		// �C���f�b�N�X�o�b�t�@���X�V����
		// ���A�b�v���[�h�o�b�t�@��V�K�ɍ쐬���A���̃o�b�t�@���玩�g�ɃR�s�[���閽�߂��R�}���h���X�g�ɓo�^����
		void updateBuffer(unsigned int handle, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, const std::vector<unsigned short>& indexDataArray);

		// �S�ẴA�b�v���[�h�p�̃o�b�t�@���폜����
		void deleteUploadBufferAll();

	private:

		tktkContainer::ResourceContainer<IndexBufferData> m_indexBufferDataArray;
	};
}
#endif // !INDEX_BUFFER_H_