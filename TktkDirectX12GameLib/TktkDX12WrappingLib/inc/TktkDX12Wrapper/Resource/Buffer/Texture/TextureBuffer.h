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
		unsigned int cpuPriorityCreate(ID3D12Device* device, const TexBufFormatParam& formatParam, const TexBuffData& dataParam);
		
		// �R�}���h���X�g���g���āuTextureBufferData�v�̃C���X�^���X�����A���̃��\�[�X�̃n���h����Ԃ�
		unsigned int gpuPriorityCreate(ID3D12Device* device, ID3D12GraphicsCommandList* commandList, const TexBufFormatParam& formatParam, const TexBuffData& dataParam);

		// �����̃t�@�C������摜�������[�h���A�R�}���h���X�g���g�킸�ɁuTextureBufferData�v�̃C���X�^���X�����A���̃��\�[�X�̃n���h����Ԃ�
		unsigned int cpuPriorityLoad(ID3D12Device* device, const std::string& texDataPath);

		// �����̃t�@�C������摜�������[�h���A�R�}���h���X�g���g���āuTextureBufferData�v�̃C���X�^���X�����A���̃��\�[�X�̃n���h����Ԃ�
		unsigned int gpuPriorityLoad(ID3D12Device* device, ID3D12GraphicsCommandList* commandList, const std::string& texDataPath);
	
		// �w��̃e�N�X�`���o�b�t�@���g�p���āA�����̃f�B�X�N���v�^�n���h���ɃV�F�[�_�[���\�[�X�r���[�����
		void createSrv(unsigned int handle, ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle) const;
		
		// �w��̃e�N�X�`���o�b�t�@�摜�̑傫�����擾����i�s�N�Z���j
		const tktkMath::Vector3& getTextureSizePx(unsigned int handle) const;

	private:

		tktkContainer::ResourceContainer<TextureBufferData> m_textureBufferDataArray;
	};
}
#endif // !TEXTURE_BUFFER_H_