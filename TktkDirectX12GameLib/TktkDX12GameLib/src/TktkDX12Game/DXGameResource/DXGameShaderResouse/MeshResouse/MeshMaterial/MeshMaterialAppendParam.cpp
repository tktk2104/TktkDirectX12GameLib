#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/MeshResouse/MeshMaterial/MeshMaterialAppendParam.h"

#include "TktkDX12Game/_MainManager/DX12GameManager.h"
#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/MeshResouse/MeshMaterial/Structs/MeshMaterialAppendParamInitParam.h"
#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/MeshResouse/MeshMaterial/Structs/MeshMaterialAppendParamUpdateFuncArgs.h"

namespace tktk
{
	MeshMaterialAppendParam::MeshMaterialAppendParam(const MeshMaterialAppendParamInitParam& initParam)
		: m_cbufferHandle(initParam.cbufferHandle)
		, m_dataSize(initParam.dataSize)
		, m_dataTopPos(initParam.cbufferDataPtr)
	{
		// �A�b�v���[�h�p�o�b�t�@�����A���̃n���h�����擾����
		m_createUploadBufferHandle = DX12GameManager::createUploadBuffer({ BufferType::constant, m_cbufferHandle, initParam.dataSize, initParam.cbufferDataPtr.get() });
	}

	MeshMaterialAppendParam::~MeshMaterialAppendParam()
	{
		DX12GameManager::eraseUploadBuffer(m_createUploadBufferHandle);
	}

	MeshMaterialAppendParam::MeshMaterialAppendParam(MeshMaterialAppendParam&& other) noexcept
		: m_createUploadBufferHandle(other.m_createUploadBufferHandle)
		, m_cbufferHandle(other.m_cbufferHandle)
		, m_dataSize(other.m_dataSize)
		, m_dataTopPos(std::move(other.m_dataTopPos))
	{
		other.m_createUploadBufferHandle = 0U;
	}

	void MeshMaterialAppendParam::updateParam(const MeshMaterialAppendParamUpdateFuncArgs& updateFuncArgs)
	{
		if (m_dataSize == updateFuncArgs.dataSize) memcpy(m_dataTopPos.get(), updateFuncArgs.dataTopPos, updateFuncArgs.dataSize);
	}

	void MeshMaterialAppendParam::updateCbuffer() const
	{
		// �萔�o�b�t�@�̃R�s�[�p�o�b�t�@���X�V����
		// TODO : �O�t���[���ƒ萔�o�b�t�@�ɕω����Ȃ��ꍇ�A�X�V���Ȃ����������
		updateCopyBuffer();

		// �萔�o�b�t�@�ɃR�s�[�o�b�t�@�̏����R�s�[����
		DX12GameManager::copyBuffer(m_createUploadBufferHandle);
	}

	void MeshMaterialAppendParam::updateCopyBuffer() const
	{
		DX12GameManager::updateUploadBuffer(m_createUploadBufferHandle, CopySourceDataCarrier(m_dataSize, m_dataTopPos.get()));
	}
}