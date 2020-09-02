#ifndef INDEX_BUFFER_DATA_H_
#define INDEX_BUFFER_DATA_H_

#include <vector>
#include <forward_list>
#include "../../../Includer/D3d12Includer.h"

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

		// �C���f�b�N�X�o�b�t�@���X�V����
		// ���A�b�v���[�h�o�b�t�@��V�K�ɍ쐬���A���̃o�b�t�@���玩�g�ɃR�s�[���閽�߂��R�}���h���X�g�ɓo�^����
		void updateBuffer(ID3D12Device* device, ID3D12GraphicsCommandList* commandList, const std::vector<unsigned short>& indexDataArray);

		// �S�ẴA�b�v���[�h�p�̃o�b�t�@���폜����
		void deleteUploadBufferAll();

		// ���g�̃o�b�t�@�̃|�C���^���擾����
		ID3D12Resource* getBufferPtr() const;

	private:

		ID3D12Resource*						m_indexBuffer		{ nullptr };
		D3D12_INDEX_BUFFER_VIEW				m_indexBufferView	{};
		std::forward_list<ID3D12Resource*>	m_uploadBufferList	{};
	};
}
#endif // !INDEX_BUFFER_DATA_H_
