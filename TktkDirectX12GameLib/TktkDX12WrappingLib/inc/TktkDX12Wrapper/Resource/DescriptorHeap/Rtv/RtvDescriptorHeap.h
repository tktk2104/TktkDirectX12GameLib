#ifndef RTV_DESCRIPTOR_HEAP_H_
#define RTV_DESCRIPTOR_HEAP_H_

#include <vector>
#include <TktkContainer/ResourceContainer/ResourceContainer.h>
#include "RtvDescriptorHeapData.h"

namespace tktk
{
	// �uRtvDescriptorHeapData�v���Ǘ�����N���X
	class RtvDescriptorHeap
	{
	public:

		explicit RtvDescriptorHeap(const tktkContainer::ResourceContainerInitParam& initParam);
		~RtvDescriptorHeap() = default;

	public:

		// �uRtvDescriptorHeapData�v�̃C���X�^���X�����A���̃��\�[�X�̃n���h����Ԃ�
		unsigned int create(ID3D12Device* device, const RtvDescriptorHeapInitParam& initParam);

		// �w��̃f�B�X�N���v�^�q�[�v���폜����
		// �������̃n���h���ɑΉ����郊�\�[�X�����������牽�����Ȃ�
		void erase(unsigned int handle);

		// �w�肵���f�B�X�N���v�^�q�[�v�̊e�r���[��CPU�A�h���X�̔z����擾����
		std::vector<D3D12_CPU_DESCRIPTOR_HANDLE> getCpuHeapHandleArray(unsigned int handle, ID3D12Device* device) const;

		// �w�肵���f�B�X�N���v�^�q�[�v�̊e�r���[���Q�Ƃ��Ă��郌���_�[�^�[�Q�b�g�o�b�t�@��ID�̔z����擾����
		const std::vector<unsigned int>& getRtBufferIdArray(unsigned int handle) const;

		// �w�肵���f�B�X�N���v�^�q�[�v�̃|�C���^���擾����
		ID3D12DescriptorHeap* getPtr(unsigned int handle) const;

		// �w�肵���f�B�X�N���v�^�q�[�v�̊e�r���[��GPU�A�h���X���R�}���h���X�g�ɓo�^����
		void setRootDescriptorTable(unsigned int handle, ID3D12Device* device, ID3D12GraphicsCommandList* commandList) const;
	
		// �w�肵���f�B�X�N���v�^�q�[�v�̎w�萔�̃����_�[�^�[�Q�b�g�r���[�ƈ����̐[�x�X�e���V���r���[���R�}���h���X�g�ɓo�^����
		void setRtv(unsigned int handle, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, unsigned int startRtvLocationIndex, unsigned int rtvCount, const D3D12_CPU_DESCRIPTOR_HANDLE* useDsvHandle) const;

		// �w�肵���f�B�X�N���v�^�q�[�v�����w��̃����_�[�^�[�Q�b�g�r���[���N���A����
		void clearRtv(unsigned int handle, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, unsigned int rtvLocationIndex, const tktkMath::Color& color) const;

	private:

		tktkContainer::ResourceContainer<RtvDescriptorHeapData> m_rtvDescriptorHeapDataArray;
	};
}
#endif // !RTV_DESCRIPTOR_HEAP_H_