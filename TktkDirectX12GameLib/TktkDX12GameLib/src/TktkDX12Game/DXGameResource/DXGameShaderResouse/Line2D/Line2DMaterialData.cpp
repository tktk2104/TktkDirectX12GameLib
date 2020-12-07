#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/Line2D/Line2DMaterialData.h"

#include "TktkDX12Game/_MainManager/DX12GameManager.h"
#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/Line2D/Structs/Line2DMaterialDrawFuncArgs.h"
#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/Line2D/Structs/Line2DCBufferData.h"

namespace tktk
{
	Line2DMaterialData::Line2DMaterialData()
	{
		// �A�b�v���[�h�p�o�b�t�@�����A���̃n���h�����擾����
		m_createUploadCbufferHandle = DX12GameManager::createUploadBuffer(UploadBufferInitParam::create(BufferType::constant, DX12GameManager::getSystemHandle(SystemCBufferType::Line2D), Line2DCBufferData()));
	}

	Line2DMaterialData::~Line2DMaterialData()
	{
		// �쐬�������_�o�b�t�@���폜����
		// ���P�x���`�揈�����Ă΂�Ȃ������ꍇ�͉������Ȃ�
		DX12GameManager::eraseVertexBuffer(m_createdVertexBufferHandle);

		// �A�b�v���[�h�p�o�b�t�@���폜����
		DX12GameManager::eraseUploadBuffer(m_createUploadCbufferHandle);
	}

	Line2DMaterialData::Line2DMaterialData(Line2DMaterialData&& other) noexcept
		: m_createdVertexBufferHandle(other.m_createdVertexBufferHandle)
		, m_createUploadCbufferHandle(other.m_createUploadCbufferHandle)
	{
		other.m_createdVertexBufferHandle	= 0U;
		other.m_createUploadCbufferHandle	= 0U;
	}

	void Line2DMaterialData::drawLine(const Line2DMaterialDrawFuncArgs& drawFuncArgs)
	{
		// �O�t���[���ō쐬�������_�o�b�t�@���폜����
		// ��������s���͉������Ȃ�
		DX12GameManager::eraseVertexBuffer(m_createdVertexBufferHandle);

		// ���g�̒��_�o�b�t�@�����
		m_createdVertexBufferHandle = DX12GameManager::createVertexBuffer(drawFuncArgs.lineVertexArray);

		// �萔�o�b�t�@�̃R�s�[�p�o�b�t�@���X�V����
		// TODO : �O�t���[���ƒ萔�o�b�t�@�ɕω����Ȃ��ꍇ�A�X�V���Ȃ����������
		updateCopyCbuffer(drawFuncArgs);

		// ���C���p�̒萔�o�b�t�@�ɃA�b�v���[�h�o�b�t�@�̏����R�s�[����
		DX12GameManager::copyBuffer(m_createUploadCbufferHandle);

		// �r���[�|�[�g��ݒ肷��
		DX12GameManager::setViewport(drawFuncArgs.viewportHandle);

		// �V�U�[��`��ݒ肷��
		DX12GameManager::setScissorRect(drawFuncArgs.scissorRectHandle);

		// �����_�[�^�[�Q�b�g��ݒ肷��i�o�b�N�o�b�t�@�[�ɒ��ŕ`�悷��ꍇ�͓��ꏈ���j
		if (drawFuncArgs.rtvDescriptorHeapHandle == DX12GameManager::getSystemHandle(SystemRtvDescriptorHeapType::BackBuffer))
		{
			DX12GameManager::setBackBufferView();
		}
		else
		{
			DX12GameManager::setRtv(drawFuncArgs.rtvDescriptorHeapHandle, 0U, 1U);
		}

		// ���C���p�̃p�C�v���C���X�e�[�g��ݒ肷��
		DX12GameManager::setPipeLineState(DX12GameManager::getSystemHandle(SystemPipeLineStateType::Line2D));

		// �u�����h�t�@�N�^�[��ݒ肷��
		DX12GameManager::setBlendFactor({ 1.0f, 1.0f, 1.0f, 1.0f });

		// ���g�̃f�B�X�N���v�^�q�[�v��ݒ肷��
		DX12GameManager::setDescriptorHeap({ { DescriptorHeapType::basic, DX12GameManager::getSystemHandle(SystemBasicDescriptorHeapType::Line2D)} });
		
		// ���C���X�g���b�v�ŕ`����s��
		DX12GameManager::setPrimitiveTopology(PrimitiveTopology::LineStrip);

		// ���g�̒��_�o�b�t�@��ݒ肷��
		DX12GameManager::setVertexBuffer(m_createdVertexBufferHandle);
		
		// �h���[�R�[��
		DX12GameManager::drawInstanced(drawFuncArgs.lineVertexArray.size(), 1U, 0U, 0U);
		
		// �o�b�N�o�b�t�@�ȊO�ɕ`�悵�Ă�����g�p���������_�[�^�[�Q�b�g�o�b�t�@���V�F�[�_�[�Ŏg�p�����Ԃɂ���
		if (drawFuncArgs.rtvDescriptorHeapHandle != DX12GameManager::getSystemHandle(SystemRtvDescriptorHeapType::BackBuffer))
		{
			DX12GameManager::unSetRtv(drawFuncArgs.rtvDescriptorHeapHandle, 0U, 1U);
		}
	}

	// �萔�o�b�t�@�̃A�b�v���[�h�p�o�b�t�@���X�V����
	void Line2DMaterialData::updateCopyCbuffer(const Line2DMaterialDrawFuncArgs& drawFuncArgs) const
	{
		Line2DCBufferData cbufferData{};
		for (unsigned int i = 0; i < 12; i++)
		{
			if (i % 4U == 3) continue;
			cbufferData.worldMatrix[i] = drawFuncArgs.worldMatrix.m[i / 4U][i % 4U];
		}
		cbufferData.lineColor = drawFuncArgs.lineColor;
		cbufferData.screenSize = DX12GameManager::getDrawGameAreaSize();

		DX12GameManager::updateUploadBuffer(m_createUploadCbufferHandle, cbufferData);
	}
}