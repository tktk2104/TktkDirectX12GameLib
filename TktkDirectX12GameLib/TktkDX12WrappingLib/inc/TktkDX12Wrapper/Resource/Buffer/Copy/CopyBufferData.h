#ifndef COPY_BUFFER_DATA_H_
#define COPY_BUFFER_DATA_H_

#include "../../../Includer/D3d12Includer.h"
#include "../BufferType.h"
#include "CopyBufferInitParam.h"

namespace tktk
{
	// �R�s�[�o�b�t�@���Ǘ�����N���X
	class CopyBufferData
	{
	public:

		CopyBufferData(ID3D12Device* device, const CopyBufferInitParam& initParam);
		~CopyBufferData();

		// �R�s�[�p�R���X�g���N�^
		CopyBufferData(ID3D12Device* device, const CopyBufferData& other);

		// ���[�u�R���X�g���N�^
		CopyBufferData(CopyBufferData&& other) noexcept;

	public:

		// �����̃|�C���^�̃f�[�^���R�s�[�o�b�t�@�ɃR�s�[����
		void updateBuffer(unsigned int bufferSize, const void* bufferDataTopPos);

		// ���g�̃R�s�[��̃o�b�t�@�̎�ނ��擾����
		BufferType getTargetBufferType() const;

		// ���g�̃R�s�[��̃o�b�t�@�̃n���h�����擾����
		unsigned int getTargetBufferHandle() const;

		// �����̃o�b�t�@�Ɏ��g�̃o�b�t�@�̓��e���R�s�[����GPU���߂�ݒ肷��
		void copyBuffer(ID3D12GraphicsCommandList* commandList, ID3D12Resource* targetBuffer) const;

	private:

		BufferType		m_targetBufferType;
		unsigned int	m_targetBufferHandle;
		unsigned int	m_copyBufferSize;
		ID3D12Resource* m_copyBuffer			{ nullptr };
	};
}

#endif // !COPY_BUFFER_DATA_H_