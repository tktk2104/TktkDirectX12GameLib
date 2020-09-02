#include "TktkDX12Game/DXGameResource/Mesh/BasicMesh/Material/BasicMeshMaterialAppendParam.h"

#include "TktkDX12Game/_MainManager/DX12GameManager.h"

namespace tktk
{
	BasicMeshMaterialAppendParam::BasicMeshMaterialAppendParam(unsigned int cbufferHandle, unsigned int dataSize, void* dataTopPos)
		: m_cbufferHandle(cbufferHandle)
		, m_dataSize(dataSize)
	{
		m_dataTopPos = std::shared_ptr<void>(dataTopPos);

		// �R�s�[�p�o�b�t�@�����A���̃n���h�����擾����
		CopyBufferInitParam initParam{};
		initParam.targetBufferType		= BufferType::constant;
		initParam.targetBufferHandle	= m_cbufferHandle;
		initParam.bufferWidth = dataSize;
		initParam.dataTopPos = dataTopPos;
		m_createCopyBufferHandle = DX12GameManager::createCopyBufferImpl(initParam);
	}

	BasicMeshMaterialAppendParam::~BasicMeshMaterialAppendParam()
	{
		DX12GameManager::eraseCopyBuffer(m_createCopyBufferHandle);
	}

	BasicMeshMaterialAppendParam::BasicMeshMaterialAppendParam(BasicMeshMaterialAppendParam&& other) noexcept
		: m_createCopyBufferHandle(other.m_createCopyBufferHandle)
		, m_cbufferHandle(other.m_cbufferHandle)
		, m_dataSize(other.m_dataSize)
		, m_dataTopPos(std::move(other.m_dataTopPos))
	{
		other.m_createCopyBufferHandle = 0U;
	}

	void BasicMeshMaterialAppendParam::updateParam(unsigned int dataSize, const void* dataTopPos)
	{
		if (m_dataSize == dataSize) memcpy(m_dataTopPos.get(), dataTopPos, dataSize);
	}

	void BasicMeshMaterialAppendParam::updateCbuffer() const
	{
		// �萔�o�b�t�@�̃R�s�[�p�o�b�t�@���X�V����
		// TODO : �O�t���[���ƒ萔�o�b�t�@�ɕω����Ȃ��ꍇ�A�X�V���Ȃ����������
		updateCopyBuffer();

		// �萔�o�b�t�@�ɃR�s�[�o�b�t�@�̏����R�s�[����
		DX12GameManager::copyBuffer(m_createCopyBufferHandle);
	}

	void BasicMeshMaterialAppendParam::updateCopyBuffer() const
	{
		DX12GameManager::updateCopyBufferImpl(m_createCopyBufferHandle, m_dataSize, m_dataTopPos.get());
	}
}