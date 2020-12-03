#ifndef INDEX_BUFFER_DATA_H_
#define INDEX_BUFFER_DATA_H_

/* std::vector */
#include <vector>

/* ID3D12Device, ID3D12GraphicsCommandList, ID3D12Resource, D3D12_INDEX_BUFFER_VIEW */
#include <d3d12.h>
#undef min
#undef max

namespace tktk
{
	// �C���f�b�N�X�o�b�t�@���Ǘ�����N���X
	class IndexBufferData
	{
	public:

		IndexBufferData(ID3D12Device* device, const std::vector<unsigned short>& indexDataArray);
		~IndexBufferData();

		// ���[�u�R���X�g���N�^
		IndexBufferData(IndexBufferData&& other) noexcept;

	public:

		// �R�}���h���X�g�ɃC���f�b�N�X�o�b�t�@��o�^����
		void set(ID3D12GraphicsCommandList* commandList) const;

		// ���g�̃o�b�t�@�̃|�C���^���擾����
		ID3D12Resource* getBufferPtr() const;

	private:

		ID3D12Resource*						m_indexBuffer		{ nullptr };
		D3D12_INDEX_BUFFER_VIEW				m_indexBufferView	{};
	};
}
#endif // !INDEX_BUFFER_DATA_H_
