#ifndef VERTEX_BUFFER_DATA_H_
#define VERTEX_BUFFER_DATA_H_

#include <forward_list>
#include "../../../Includer/D3d12Includer.h"
#include "VertexDataCarrier.h"

namespace tktk
{
	// ���_�o�b�t�@���Ǘ�����N���X
	class VertexBufferData
	{
	public:

		VertexBufferData(ID3D12Device* device, const VertexDataCarrier& vertexData);
		~VertexBufferData();

		// ���[�u�R���X�g���N�^
		VertexBufferData(VertexBufferData&& other) noexcept;

	public:

		// �R�}���h���X�g�ɒ��_�o�b�t�@��o�^����
		void set(ID3D12GraphicsCommandList* commandList) const;

		// ���g�̃o�b�t�@�̃|�C���^���擾����
		ID3D12Resource* getBufferPtr() const;

	private:

		ID3D12Resource*						m_vertexBuffer		{ nullptr };
		D3D12_VERTEX_BUFFER_VIEW			m_vertexBufferView	{};
	};
}
#endif // !VERTEX_BUFFER_DATA_H_