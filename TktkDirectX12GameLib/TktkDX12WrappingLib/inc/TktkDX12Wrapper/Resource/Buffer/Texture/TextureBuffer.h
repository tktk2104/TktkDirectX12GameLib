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
		
		// �R�}���h���X�g���g�킸�ɁuTextureBufferData�v�̃C���X�^���X�����A���̃��\�[�X�̃n���h����Ԃ�
		size_t cpuPriorityCreate(ID3D12Device* device, const TexBufFormatParam& formatParam, const TexBuffData& dataParam);
		
		// �R�}���h���X�g���g���āuTextureBufferData�v�̃C���X�^���X�����A���̃��\�[�X�̃n���h����Ԃ�
		size_t gpuPriorityCreate(ID3D12Device* device, ID3D12GraphicsCommandList* commandList, const TexBufFormatParam& formatParam, const TexBuffData& dataParam);

		// �����̃t�@�C������摜�������[�h���A�R�}���h���X�g���g�킸�ɁuTextureBufferData�v�̃C���X�^���X�����A���̃��\�[�X�̃n���h����Ԃ�
		size_t cpuPriorityLoad(ID3D12Device* device, const std::string& texDataPath);

		// �����̃t�@�C������摜�������[�h���A�R�}���h���X�g���g���āuTextureBufferData�v�̃C���X�^���X�����A���̃��\�[�X�̃n���h����Ԃ�
		size_t gpuPriorityLoad(ID3D12Device* device, ID3D12GraphicsCommandList* commandList, const std::string& texDataPath);
	
		// �w��̃e�N�X�`���o�b�t�@���폜����
		// �������̃n���h���ɑΉ����郊�\�[�X�����������牽�����Ȃ�
		void erase(size_t handle);

		// �w��̃e�N�X�`���o�b�t�@���g�p���āA�����̃f�B�X�N���v�^�n���h���ɃV�F�[�_�[���\�[�X�r���[�����
		void createSrv(size_t handle, ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle) const;
		
		// �w��̃e�N�X�`���o�b�t�@�摜�̑傫�����擾����i�s�N�Z���j
		const tktkMath::Vector3& getTextureSizePx(size_t handle) const;

		// �w��̃e�N�X�`���o�b�t�@�̃|�C���^���擾����
		ID3D12Resource* getBufferPtr(size_t handle) const;

		// �w��̃e�N�X�`���o�b�t�@�̃R�s�[�Ɏg�p����t�b�g�v�����g�w��̐ݒ���\���̂����
		D3D12_TEXTURE_COPY_LOCATION createSrcCopyLoaction(size_t handle) const;

	private:

		tktkContainer::ResourceContainer<TextureBufferData> m_textureBufferDataArray;
	};
}
#endif // !TEXTURE_BUFFER_H_