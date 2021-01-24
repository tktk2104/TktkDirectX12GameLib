#ifndef VERTEX_BUFFER_DATA_H_
#define VERTEX_BUFFER_DATA_H_

/* ID3D12Device, ID3D12GraphicsCommandList, ID3D12Resource, D3D12_VERTEX_BUFFER_VIEW */
#include <d3d12.h>
#undef min
#undef max

#include "VertexDataCarrier.h"

namespace tktk
{
	// ���_�o�b�t�@���Ǘ�����N���X
	class VertexBufferData
	{
	public:

		VertexBufferData(ID3D12Device* device, size_t strideDataSize, size_t allDataSize);
		~VertexBufferData();

		// ���[�u�R���X�g���N�^
		VertexBufferData(VertexBufferData&& other) noexcept;

	public:

		// �R�}���h���X�g�ɒ��_�o�b�t�@��o�^����
		void set(ID3D12GraphicsCommandList* commandList) const;

		// ���g�̃o�b�t�@�̃|�C���^���擾����
		ID3D12Resource* getBufferPtr() const;

		// ���g�̃o�b�t�@�r���[���擾����
		const D3D12_VERTEX_BUFFER_VIEW& getBufferView() const;

	private:

		ID3D12Resource*						m_vertexBuffer		{ nullptr };
		D3D12_VERTEX_BUFFER_VIEW			m_vertexBufferView	{};
	};
}
#endif // !VERTEX_BUFFER_DATA_H_