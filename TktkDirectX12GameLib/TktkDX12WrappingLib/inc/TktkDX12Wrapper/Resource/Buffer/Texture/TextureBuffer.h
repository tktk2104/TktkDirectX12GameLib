#ifndef TEXTURE_BUFFER_H_
#define TEXTURE_BUFFER_H_

#include <string>
#include <TktkContainer/ResourceContainer/ResourceContainer.h>
#include "TextureBufferData.h"

namespace tktk
{
	// �uTextureBufferData�v���Ǘ�����N���X
	class TextureBuffer
	{
	public:

		explicit TextureBuffer(const tktkContainer::ResourceContainerInitParam& initParam);
		~TextureBuffer() = default;

	public:
		
		// �uTextureBufferData�v�̃C���X�^���X�����A���̃��\�[�X�̃n���h����Ԃ�
		size_t create(ID3D12Device* device, const TexBufFormatParam& formatParam, const TexBuffData& dataParam);

		// �w��̃e�N�X�`���o�b�t�@���폜����
		// �������̃n���h���ɑΉ����郊�\�[�X�����������牽�����Ȃ�
		void erase(size_t handle);

		// �w��̃e�N�X�`���o�b�t�@���g�p���āA�����̃f�B�X�N���v�^�n���h���ɃV�F�[�_�[���\�[�X�r���[�����
		void createSrv(size_t handle, ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle) const;
		
		// �w��̃e�N�X�`���o�b�t�@�摜�̑傫�����擾����i�s�N�Z���j
		const tktkMath::Vector3& getTextureSizePx(size_t handle) const;

		// �w��̃e�N�X�`���o�b�t�@�̃|�C���^���擾����
		ID3D12Resource* getBufferPtr(size_t handle) const;

		// �w��̃e�N�X�`���o�b�t�@�̂P�s�N�Z���̃f�[�^�̃o�C�g�T�C�Y���擾����
		size_t getPixDataSizeByte(size_t handle) const;

		// �w��̃e�N�X�`���o�b�t�@�̃R�s�[�Ɏg�p����t�b�g�v�����g�w��̐ݒ���\���̂����
		D3D12_TEXTURE_COPY_LOCATION createSrcCopyLoaction(size_t handle) const;

	private:

		tktkContainer::ResourceContainer<TextureBufferData> m_textureBufferDataArray;
	};
}
#endif // !TEXTURE_BUFFER_H_