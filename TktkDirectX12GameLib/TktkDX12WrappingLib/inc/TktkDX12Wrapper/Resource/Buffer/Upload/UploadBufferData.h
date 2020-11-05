#ifndef COPY_BUFFER_DATA_H_
#define COPY_BUFFER_DATA_H_

#include "../../../Includer/D3d12Includer.h"
#include "../BufferType.h"
#include "UploadBufferInitParam.h"
#include "../CopySourceDataCarrier.h"

namespace tktk
{
	// �A�b�v���[�h�o�b�t�@���Ǘ�����N���X
	class UploadBufferData
	{
	public:

		UploadBufferData(ID3D12Device* device, const UploadBufferInitParam& initParam);
		~UploadBufferData();

		// �R�s�[�p�R���X�g���N�^
		UploadBufferData(ID3D12Device* device, const UploadBufferData& other);

		// ���[�u�R���X�g���N�^
		UploadBufferData(UploadBufferData&& other) noexcept;

	public:

		// �����̃|�C���^�̃f�[�^���A�b�v���[�h�o�b�t�@�ɃR�s�[����
		void updateBuffer(const CopySourceDataCarrier& bufferData);

		// ���g�̃A�b�v���[�h��̃o�b�t�@�̎�ނ��擾����
		BufferType getTargetBufferType() const;

		// ���g�̃A�b�v���[�h��̃o�b�t�@�̃n���h�����擾����
		size_t getTargetBufferHandle() const;

		// �����̃o�b�t�@�Ɏ��g�̃o�b�t�@�̓��e���A�b�v���[�h����GPU���߂��s��
		void copyBuffer(ID3D12GraphicsCommandList* commandList, ID3D12Resource* targetBuffer) const;

	private:

		BufferType		m_targetBufferType;
		size_t			m_targetBufferHandle;
		size_t			m_copyBufferSize;
		ID3D12Resource* m_uploadBuffer		{ nullptr };
	};
}
#endif // !COPY_BUFFER_DATA_H_