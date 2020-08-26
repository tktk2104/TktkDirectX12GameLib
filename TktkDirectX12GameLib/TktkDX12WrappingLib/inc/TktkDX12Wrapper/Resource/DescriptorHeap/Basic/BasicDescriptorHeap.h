#ifndef BASIC_DESCRIPTOR_HEAP_H_
#define BASIC_DESCRIPTOR_HEAP_H_

#include <vector>
#include <TktkContainer/ResourceContainer/ResourceContainer.h>
#include "BasicDescriptorHeapData.h"

namespace tktk
{
	// �uBasicDescriptorHeapData�v���Ǘ�����N���X
	class BasicDescriptorHeap
	{
	public:

		explicit BasicDescriptorHeap(const tktkContainer::ResourceContainerInitParam& initParam);
		~BasicDescriptorHeap() = default;

	public:

		// �uBasicDescriptorHeapData�v�̃C���X�^���X�����A���̃��\�[�X�̃n���h����Ԃ�
		unsigned int create(ID3D12Device* device, const BasicDescriptorHeapInitParam& initParam);

		// �w��̃f�B�X�N���v�^�q�[�v���폜����
		// �������̃n���h���ɑΉ����郊�\�[�X�����������牽�����Ȃ�
		void erase(unsigned int handle);

		// �w�肵���f�B�X�N���v�^�q�[�v�̊e�r���[��CPU�A�h���X�̔z����擾����
		std::vector<D3D12_CPU_DESCRIPTOR_HANDLE> getCpuHeapHandleArray(unsigned int handle, ID3D12Device* device) const;

		// �w�肵���f�B�X�N���v�^�q�[�v�̃|�C���^���擾����
		ID3D12DescriptorHeap* getPtr(unsigned int handle) const;

		// �w�肵���f�B�X�N���v�^�q�[�v�̊e�r���[��GPU�A�h���X���R�}���h���X�g�ɓo�^����
		void setRootDescriptorTable(unsigned int handle, ID3D12Device* device, ID3D12GraphicsCommandList* commandList) const;

	private:

		tktkContainer::ResourceContainer<BasicDescriptorHeapData> m_basicDescriptorHeapDataArray;
	};
}
#endif // !BASIC_DESCRIPTOR_HEAP_H_