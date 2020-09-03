#ifndef CONSTANT_BUFFER_DATA_H_
#define CONSTANT_BUFFER_DATA_H_

#include <forward_list>
#include "../../../Includer/D3d12Includer.h"

namespace tktk
{
	// �萔�o�b�t�@���Ǘ�����N���X
	class ConstantBufferData
	{
	public:

		ConstantBufferData(ID3D12Device* device, unsigned int constantBufferTypeSize, const void* constantBufferDataTopPos);
		~ConstantBufferData();

		// ���[�u�R���X�g���N�^
		ConstantBufferData(ConstantBufferData&& other) noexcept;

	public:

		// �����̃f�B�X�N���v�^�n���h���ɒ萔�o�b�t�@�r���[�����
		void createCbv(ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle) const;

		// �萔�o�b�t�@���X�V����
		// ���A�b�v���[�h�o�b�t�@��V�K�ɍ쐬���A���̃o�b�t�@���玩�g�ɃR�s�[���閽�߂��R�}���h���X�g�ɓo�^����
		void updateBuffer(ID3D12Device* device, ID3D12GraphicsCommandList* commandList, unsigned int constantBufferTypeSize, const void* constantBufferDataTopPos);

		// �S�ẴA�b�v���[�h�p�̃o�b�t�@���폜����
		void deleteUploadBufferAll();

		// ���g�̃o�b�t�@�̃|�C���^���擾����
		ID3D12Resource* getBufferPtr() const;

	private:

		ID3D12Resource*						m_constantBuffer{ nullptr };
	};
}
#endif // !CONSTANT_BUFFER_DATA_H_