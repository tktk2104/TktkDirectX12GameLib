#ifndef CONSTANT_BUFFER_DATA_H_
#define CONSTANT_BUFFER_DATA_H_

#include <forward_list>
#include "../../../Includer/D3d12Includer.h"
#include "../CopySourceDataCarrier.h"

namespace tktk
{
	// �萔�o�b�t�@���Ǘ�����N���X
	class ConstantBufferData
	{
	public:

		ConstantBufferData(ID3D12Device* device, const CopySourceDataCarrier& constantBufferData);
		~ConstantBufferData();

		// ���[�u�R���X�g���N�^
		ConstantBufferData(ConstantBufferData&& other) noexcept;

	public:

		// �����̃f�B�X�N���v�^�n���h���ɒ萔�o�b�t�@�r���[�����
		void createCbv(ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle) const;

		// ���g�̃o�b�t�@�̃|�C���^���擾����
		ID3D12Resource* getBufferPtr() const;

	private:

		ID3D12Resource*						m_constantBuffer{ nullptr };
	};
}
#endif // !CONSTANT_BUFFER_DATA_H_