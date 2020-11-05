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
		size_t create(ID3D12Device* device, const CopySourceDataCarrier& constantBufferData);

		// �w��̒萔�o�b�t�@���폜����
		// �������̃n���h���ɑΉ����郊�\�[�X�����������牽�����Ȃ�
		void erase(size_t handle);
	
		// �w��̒萔�o�b�t�@���g�p���āA�����̃f�B�X�N���v�^�n���h���ɒ萔�o�b�t�@�r���[�����
		void createCbv(size_t handle, ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle) const;

		// �w��̒萔�o�b�t�@�̃|�C���^���擾����
		ID3D12Resource* getBufferPtr(size_t handle) const;

	private:

		tktkContainer::ResourceContainer<ConstantBufferData> m_constantBufferDataArray;
	};
}
#endif // !CONSTANT_BUFFER_H_