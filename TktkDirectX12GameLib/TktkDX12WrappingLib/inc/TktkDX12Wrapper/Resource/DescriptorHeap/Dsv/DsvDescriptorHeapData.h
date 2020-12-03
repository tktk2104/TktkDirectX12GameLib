#ifndef DSV_DESCRIPTOR_HEAP_DATA_H_
#define DSV_DESCRIPTOR_HEAP_DATA_H_

/* std::vector */
#include <vector>

/* ID3D12Device, ID3D12GraphicsCommandList, ID3D12DescriptorHeap */
#include <d3d12.h>
#undef min
#undef max

#include <TktkMath/Structs/Color.h>
#include "DsvDescriptorHeapInitParam.h"

namespace tktk
{
	// �[�x�X�e���V���r���[�p�̃f�B�X�N���v�^�q�[�v�N���X
	class DsvDescriptorHeapData
	{
	public:

		DsvDescriptorHeapData(ID3D12Device* device, const DsvDescriptorHeapInitParam& initParam);
		~DsvDescriptorHeapData();

		// ���[�u�R���X�g���N�^
		DsvDescriptorHeapData(DsvDescriptorHeapData&& other) noexcept;

	public:

		// �e�r���[��CPU�A�h���X�̔z����擾����
		std::vector<D3D12_CPU_DESCRIPTOR_HANDLE> getCpuHeapHandleArray(ID3D12Device* device) const;

		// �e�r���[���Q�Ƃ��Ă���[�x�X�e���V���o�b�t�@��ID�̔z����擾����
		const std::vector<size_t>& getDsBufferHandleArray() const;

		// �f�B�X�N���v�^�q�[�v���܂Ƃ߂ăR�}���h���X�g�ɓo�^���邽�߂ɂ���Q�b�^�[
		ID3D12DescriptorHeap* getPtr() const;

		// �e�r���[��GPU�A�h���X���R�}���h���X�g�ɓo�^����
		void setRootDescriptorTable(ID3D12Device* device, ID3D12GraphicsCommandList* commandList) const;

		// �����_�[�^�[�Q�b�g�r���[��o�^�����ɐ[�x�X�e���V���r���[���R�}���h���X�g�ɓo�^����
		void setOnlyDsv(ID3D12Device* device, ID3D12GraphicsCommandList* commandList) const;

		// �w��̐[�x�X�e���V���r���[���N���A����
		void clearDsv(ID3D12Device* device, ID3D12GraphicsCommandList* commandList) const;

	private:

		std::vector<size_t>		m_dsBufferHandleArray	{};
		ID3D12DescriptorHeap*	m_descriptorHeap		{ nullptr };
	};
}
#endif // !DSV_DESCRIPTOR_HEAP_DATA_H_