#ifndef CONSTANT_BUFFER_H_
#define CONSTANT_BUFFER_H_

#include <TktkContainer/ResourceContainer/ResourceContainer.h>
#include "ConstantBufferData.h"

namespace tktk
{
	// �uConstantBufferData�v���Ǘ�����N���X
	class ConstantBuffer
	{
	public:

		explicit ConstantBuffer(const tktkContainer::ResourceContainerInitParam& initParam);
		~ConstantBuffer() = default;

	public:

		// �uConstantBufferData�v�̃C���X�^���X�����A���̃��\�[�X�̃n���h����Ԃ�
		unsigned int create(ID3D12Device* device, unsigned int constantBufferTypeSize, const void* constantBufferDataTopPos);
	
		// �w��̒萔�o�b�t�@���g�p���āA�����̃f�B�X�N���v�^�n���h���ɒ萔�o�b�t�@�r���[�����
		void createCbv(unsigned int handle, ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle) const;
	
		// �w��̒萔�o�b�t�@���X�V����
		// ���A�b�v���[�h�o�b�t�@��V�K�ɍ쐬���A���̃o�b�t�@���玩�g�ɃR�s�[���閽�߂��R�}���h���X�g�ɓo�^����
		void updateBuffer(unsigned int handle, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, unsigned int constantBufferTypeSize, const void* constantBufferDataTopPos);

		// �S�ẴA�b�v���[�h�p�̃o�b�t�@���폜����
		void deleteUploadBufferAll();

	private:

		tktkContainer::ResourceContainer<ConstantBufferData> m_constantBufferDataArray;
	};
}
#endif // !CONSTANT_BUFFER_H_