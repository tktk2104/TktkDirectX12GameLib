#ifndef RTV_DESCRIPTOR_HEAP_DATA_H_
#define RTV_DESCRIPTOR_HEAP_DATA_H_

/* std::vector */
#include <vector>

/* ID3D12Device, ID3D12GraphicsCommandList, D3D12_CPU_DESCRIPTOR_HANDLE, ID3D12DescriptorHeap */
#include <d3d12.h>
#undef min
#undef max


#include <TktkMath/Structs/Color.h>
#include "RtvDescriptorHeapInitParam.h"

namespace tktk
{
	// �����_�[�^�[�Q�b�g�r���[�p�̃f�B�X�N���v�^�q�[�v�N���X
	class RtvDescriptorHeapData
	{
	public:

		RtvDescriptorHeapData(ID3D12Device* device, const RtvDescriptorHeapInitParam& initParam);
		~RtvDescriptorHeapData();

		// ���[�u�R���X�g���N�^
		RtvDescriptorHeapData(RtvDescriptorHeapData&& other) noexcept;

	public:

		// �e�r���[��CPU�A�h���X�̔z����擾����
		std::vector<D3D12_CPU_DESCRIPTOR_HANDLE> getCpuHeapHandleArray(ID3D12Device* device) const;

		// �e�r���[���Q�Ƃ��Ă��郌���_�[�^�[�Q�b�g�o�b�t�@��ID�̔z����擾����
		const std::vector<size_t>& getRtBufferHandleArray() const;

		// �f�B�X�N���v�^�q�[�v���܂Ƃ߂ăR�}���h���X�g�ɓo�^���邽�߂ɂ���Q�b�^�[
		ID3D12DescriptorHeap* getPtr() const;

		// �e�r���[��GPU�A�h���X���R�}���h���X�g�ɓo�^����
		void setRootDescriptorTable(ID3D12Device* device, ID3D12GraphicsCommandList* commandList) const;

		// �w�萔�̃����_�[�^�[�Q�b�g�r���[�ƈ����̐[�x�X�e���V���r���[���R�}���h���X�g�ɓo�^����
		void setRtv(ID3D12Device* device, ID3D12GraphicsCommandList* commandList, size_t startRtvLocationIndex, unsigned int rtvCount, const D3D12_CPU_DESCRIPTOR_HANDLE* useDsvHandle) const;

	private:

		std::vector<size_t>			m_rtBufferHandleArray	{};
		ID3D12DescriptorHeap*		m_descriptorHeap		{ nullptr };
	};
}
#endif // !RTV_DESCRIPTOR_HEAP_DATA_H_