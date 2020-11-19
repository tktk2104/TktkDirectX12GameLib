#include "TktkDX12BaseComponents/3D/ShadowMapWriter/WriteMeshShadowMapFuncRunner.h"

#include "TktkDX12Game/_MainManager/DX12GameManager.h"
#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/MeshResouse/Mesh/Structs/CameraCbuffer.h"

namespace tktk
{
	WriteMeshShadowMapFuncRunner::WriteMeshShadowMapFuncRunner(size_t meshHandle, bool useBone, size_t skeletonHandle)
		: ComponentBase(-1000.0f)
		, m_meshHandle(meshHandle)
		, m_useBone(useBone)
		, m_skeletonHandle(skeletonHandle)
	{
	}

	void WriteMeshShadowMapFuncRunner::start()
	{
		// �A�b�v���[�h�p�o�b�t�@�����A���̃n���h�����擾����
		m_createUploadCameraCbufferHandle = DX12GameManager::createUploadBuffer(UploadBufferInitParam::create(BufferType::constant, DX12GameManager::getSystemHandle(SystemCBufferType::Camera), CameraCbuffer()));
		
		// �����X�P���g�����ݒ肳��Ă�����A�b�v���[�h�p�o�b�t�@�����
		if (m_skeletonHandle != 0U) m_createUploadBoneMatrixCbufferHandle = DX12GameManager::createSkeletonUploadBufferHandle(m_skeletonHandle);
	}

	void WriteMeshShadowMapFuncRunner::onDestroy()
	{
		// �A�b�v���[�h�p�o�b�t�@���폜����
		DX12GameManager::eraseUploadBuffer(m_createUploadCameraCbufferHandle);

		DX12GameManager::eraseUploadBuffer(m_createUploadBoneMatrixCbufferHandle);
	}

	void WriteMeshShadowMapFuncRunner::draw() const
	{
		// �J�������萔�o�b�t�@�̍X�V
		updateCameraCbuffer();

		// �����X�P���g�������ݒ肾������
		if (m_skeletonHandle == 0U)
		{
			// �{�[�����̒萔�o�b�t�@��P�ʍs��ŏ�����
			DX12GameManager::resetBoneMatrixCbuffer();
		}
		// �����łȂ����
		else
		{
			// �{�[���s��̒萔�o�b�t�@���X�V����
			DX12GameManager::updateBoneMatrixCbuffer(m_skeletonHandle, m_createUploadBoneMatrixCbufferHandle);
		}

		if (m_useBone)
		{
			// �X�L�j���O���b�V���V���h�E�}�b�v��`�悷��
			DX12GameManager::writeMeshShadowMapUseBone(m_meshHandle);
		}
		else
		{
			// �V���h�E�}�b�v��`�悷��
			DX12GameManager::writeMeshShadowMap(m_meshHandle);
		}
	}

	void WriteMeshShadowMapFuncRunner::updateCameraCbuffer() const
	{
		// �J�������萔�o�b�t�@�`��
		CameraCbuffer transformBufferData{};

		// �g�p����J�����̃r���[�s��
		transformBufferData.viewMatrix = DX12GameManager::getViewMatrix(DX12GameManager::getSystemHandle(SystemCameraType::DefaultShadowMapCamera));

		// �g�p����J�����̃v���W�F�N�V�����s��
		transformBufferData.projectionMatrix = DX12GameManager::getProjectionMatrix(DX12GameManager::getSystemHandle(SystemCameraType::DefaultShadowMapCamera));

		// �萔�o�b�t�@�̃A�b�v���[�h�p�o�b�t�@���X�V����
		// TODO : �O�t���[���ƒ萔�o�b�t�@�ɕω����Ȃ��ꍇ�A�X�V���Ȃ����������
		DX12GameManager::updateUploadBuffer(m_createUploadCameraCbufferHandle, transformBufferData);

		// ���W�ϊ��p�̒萔�o�b�t�@�ɃA�b�v���[�h�o�b�t�@�̏����R�s�[����
		DX12GameManager::copyBuffer(m_createUploadCameraCbufferHandle);
	}
}