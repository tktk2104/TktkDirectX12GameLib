#ifndef DESCRIPTOR_HEAP_H_
#define DESCRIPTOR_HEAP_H_

#include <memory>	// std::unique_ptr
#include <TktkMath/Structs/Color.h>
#include "../../Includer/D3d12Includer.h"
#include "DescriptorHeapInitParamIncluder.h"
#include "DescriptorHeapParam.h"
#include "DescriptorHeapNum.h"

namespace tktk
{
	// �O���錾�B
	class BasicDescriptorHeap;
	class RtvDescriptorHeap;
	class DsvDescriptorHeap;

	// �R��ނ̃f�B�X�N���v�^�q�[�v���Ǘ�����N���X
	class DescriptorHeap
	{
	public:

		explicit DescriptorHeap(const DescriptorHeapNum& initParam);
		~DescriptorHeap();

	public: /* �R�}���h���X�g�ɓo�^���鏈�� */

		// �w��̃f�B�X�N���v�^�q�[�v�𕡐��܂Ƃ߂ăR�}���h���X�g�ɓo�^����
		void set(ID3D12Device* device, ID3D12GraphicsCommandList* commandList, const std::vector<DescriptorHeapParam>& heapParamArray) const;

	public: /* �����_�[�^�[�Q�b�g�A�[�x�X�e���V�����R�}���h���X�g�ɓo�^���鏈�� */

		// �����_�[�^�[�Q�b�g�r���[���R�}���h���X�g�ɓo�^����
		void setRtv(size_t rtvHandle, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, size_t startRtvLocationIndex, unsigned int rtvCount) const;
		
		// �����_�[�^�[�Q�b�g�r���[�Ɛ[�x�X�e���V���r���[���R�}���h���X�g�ɓo�^����
		void setRtvAndDsv(size_t rtvHandle, size_t dsvHandle, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, size_t startRtvLocation, unsigned int rtvCount) const;
		
		// �����_�[�^�[�Q�b�g�r���[��o�^�����Ɏw�肵���f�B�X�N���v�^�q�[�v�̐[�x�X�e���V���r���[���R�}���h���X�g�ɓo�^����
		void setOnlyDsv(size_t handle, ID3D12Device* device, ID3D12GraphicsCommandList* commandList) const;
		
	public: /* �f�B�X�N���v�^�q�[�v�����e�r���[�̃N���A���� */
		
		// �w�肵�������_�[�^�[�Q�b�g�p�̃f�B�X�N���v�^�q�[�v�����w��̃����_�[�^�[�Q�b�g�r���[���N���A����
		void clearRtv(size_t handle, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, size_t rtvLocationIndex, const tktkMath::Color& color) const;
		
		// �[�x�X�e���V���r���[��S�ăN���A����
		void clearDsvAll(ID3D12Device* device, ID3D12GraphicsCommandList* commandList) const;

	public: /* �쐬���� */

		// �ʏ�̃f�B�X�N���v�^�q�[�v�����
		size_t createBasicDescriptorHeap(ID3D12Device* device, const BasicDescriptorHeapInitParam& initParam);
		
		// �����_�[�^�[�Q�b�g�p�̃f�B�X�N���v�^�q�[�v�����
		size_t createRtvDescriptorHeap(ID3D12Device* device, const RtvDescriptorHeapInitParam& initParam);
		
		// �[�x�X�e���V���p�̃f�B�X�N���v�^�q�[�v�����
		size_t createDsvDescriptorHeap(ID3D12Device* device, const DsvDescriptorHeapInitParam& initParam);

	public: /* �폜���� */

		// �w��̒ʏ�̃f�B�X�N���v�^�q�[�v���폜����
		// �������̃n���h���ɑΉ����郊�\�[�X�����������牽�����Ȃ�
		void eraseBasicDescriptorHeap(size_t handle);

		// �w��̃����_�[�^�[�Q�b�g�p�̃f�B�X�N���v�^�q�[�v���폜����
		// �������̃n���h���ɑΉ����郊�\�[�X�����������牽�����Ȃ�
		void eraseRtvDescriptorHeap(size_t handle);

		// �w��̐[�x�X�e���V���p�̃f�B�X�N���v�^�q�[�v���폜����
		// �������̃n���h���ɑΉ����郊�\�[�X�����������牽�����Ȃ�
		void eraseDsvDescriptorHeap(size_t handle);

	public: /* CPU�n���h���̎擾���� */

		// �w�肵���ʏ�̃f�B�X�N���v�^�q�[�v�̊e�r���[��CPU�A�h���X�̔z����擾����
		std::vector<D3D12_CPU_DESCRIPTOR_HANDLE> getCpuBasicHeapHandleArray(size_t handle, ID3D12Device* device) const;
		
		// �w�肵�������_�[�^�[�Q�b�g�p�̃f�B�X�N���v�^�q�[�v�̊e�r���[��CPU�A�h���X�̔z����擾����
		std::vector<D3D12_CPU_DESCRIPTOR_HANDLE> getCpuRtvHeapHandleArray(size_t handle, ID3D12Device* device) const;
		
		// �w�肵���[�x�X�e���V���p�̃f�B�X�N���v�^�q�[�v�̊e�r���[��CPU�A�h���X�̔z����擾����
		std::vector<D3D12_CPU_DESCRIPTOR_HANDLE> getCpuDsvHeapHandleArray(size_t handle, ID3D12Device* device) const;

	public: /* �f�B�X�N���v�^�q�[�v�����e�r���[���Q�Ƃ��Ă���o�b�t�@��ID���擾���鏈�� */

		// �w�肵�������_�[�^�[�Q�b�g�p�̃f�B�X�N���v�^�q�[�v�̊e�r���[���Q�Ƃ��Ă��郌���_�[�^�[�Q�b�g�o�b�t�@��ID�̔z����擾����
		const std::vector<size_t>& getRtvDescriptorHeapUseBufferHandleArray(size_t handle) const;
		
		// �w�肵���[�x�X�e���V���p�̃f�B�X�N���v�^�q�[�v�̊e�r���[���Q�Ƃ��Ă���[�x�X�e���V���o�b�t�@��ID�̔z����擾����
		const std::vector<size_t>& getDsvDescriptorHeapUseBufferHandleArray(size_t handle) const;

	private:

		std::unique_ptr<BasicDescriptorHeap>	m_basicDescriptorHeap;
		std::unique_ptr<RtvDescriptorHeap>		m_rtvDescriptorHeap;
		std::unique_ptr<DsvDescriptorHeap>		m_dsvDescriptorHeap;
	};
}
#endif // !DESCRIPTOR_HEAP_H_