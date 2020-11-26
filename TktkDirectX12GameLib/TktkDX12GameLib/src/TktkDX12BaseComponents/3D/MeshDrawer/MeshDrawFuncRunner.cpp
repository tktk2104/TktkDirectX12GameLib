#include "TktkDX12BaseComponents/3D/MeshDrawer/MeshDrawFuncRunner.h"

#include "TktkDX12BaseComponents/3D/MeshDrawer/MeshDrawFuncRunnerInitParam.h"
#include "TktkDX12Game/_MainManager/DX12GameManager.h"
#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/MeshResouse/Mesh/Structs/CameraCbuffer.h"
#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/MeshResouse/Mesh/Structs/MeshShadowMapCBuffer.h"

namespace tktk
{
	MeshDrawFuncRunner::MeshDrawFuncRunner(size_t meshHandle, const MeshDrawFuncRunnerInitParam& initParam)
		: ComponentBase(initParam.m_drawPriority)
		, m_useBone(initParam.m_useBone)
		, m_meshHandle(meshHandle)
		, m_rtvDescriptorHeapHandle(initParam.m_rtvDescriptorHeapHandle)
		, m_lightHandle(initParam.m_lightHandle)
		, m_cameraHandle(initParam.m_cameraHandle)
		, m_shadowMapCameraHandle(initParam.m_shadowMapCameraHandle)

		, m_skeletonHandle(initParam.m_skeletonHandle)
	{
	}

	void MeshDrawFuncRunner::start()
	{
		// �A�b�v���[�h�p�o�b�t�@�����A���̃n���h�����擾����
		m_createUploadCameraCbufferHandle		= DX12GameManager::createUploadBuffer(UploadBufferInitParam::create(BufferType::constant, DX12GameManager::getSystemHandle(SystemCBufferType::Camera), CameraCbuffer()));
		m_createUploadShadowMapCbufferHandle	= DX12GameManager::createUploadBuffer(UploadBufferInitParam::create(BufferType::constant, DX12GameManager::getSystemHandle(SystemCBufferType::ShadowMap), MeshShadowMapCBuffer()));
	
		// �����X�P���g�����ݒ肳��Ă�����A�b�v���[�h�p�o�b�t�@�����
		if (m_skeletonHandle != 0U) m_createUploadBoneMatrixCbufferHandle = DX12GameManager::createSkeletonUploadBufferHandle(m_skeletonHandle);
	}

	void MeshDrawFuncRunner::onDestroy()
	{
		// �A�b�v���[�h�p�o�b�t�@���폜����
		DX12GameManager::eraseUploadBuffer(m_createUploadCameraCbufferHandle);
		DX12GameManager::eraseUploadBuffer(m_createUploadShadowMapCbufferHandle);

		DX12GameManager::eraseUploadBuffer(m_createUploadBoneMatrixCbufferHandle);
	}

	void MeshDrawFuncRunner::update()
	{
		DX12GameManager::clearMeshInstanceParam(m_meshHandle);
	}

	void MeshDrawFuncRunner::draw() const
	{
		// �J�������萔�o�b�t�@�̍X�V
		updateCameraCbuffer();

		// �V���h�E�}�b�v�p�̒萔�o�b�t�@�̍X�V���s��
		updateShadowMapCbuffer();

		// ���b�V���`��ɕK�v�Ȓl
		MeshDrawFuncBaseArgs baseArgs{};

		// �g�p����r���[�|�[�g�n���h��
		baseArgs.viewportHandle = DX12GameManager::getSystemHandle(SystemViewportType::Basic);

		// �g�p����V�U�[��`�n���h��
		baseArgs.scissorRectHandle = DX12GameManager::getSystemHandle(SystemScissorRectType::Basic);

		// �g�p���郌���_�[�^�[�Q�b�g�f�B�X�N���v�^�q�[�v�n���h��
		baseArgs.rtvDescriptorHeapHandle = m_rtvDescriptorHeapHandle;

		// �g�p����[�x�X�e���V���f�B�X�N���v�^�q�[�v�n���h��
		baseArgs.dsvDescriptorHeapHandle = DX12GameManager::getSystemHandle(SystemDsvDescriptorHeapType::Basic);

		// �g�p���郉�C�g�ԍ�
		baseArgs.lightHandle = m_lightHandle;

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
			// �X�L�j���O���b�V����`�悷��
			DX12GameManager::drawMeshUseBone(m_meshHandle, baseArgs);
		}
		else
		{
			// ���b�V����`�悷��
			DX12GameManager::drawMesh(m_meshHandle, baseArgs);
		}
	}

	void MeshDrawFuncRunner::updateCameraCbuffer() const
	{
		// �J�������萔�o�b�t�@�`��
		CameraCbuffer transformBufferData{};

		// �g�p����J�����̃r���[�s��
		transformBufferData.viewMatrix = DX12GameManager::getViewMatrix(m_cameraHandle);

		// �g�p����J�����̃v���W�F�N�V�����s��
		transformBufferData.projectionMatrix = DX12GameManager::getProjectionMatrix(m_cameraHandle);

		// �萔�o�b�t�@�̃A�b�v���[�h�p�o�b�t�@���X�V����
		// TODO : �O�t���[���ƒ萔�o�b�t�@�ɕω����Ȃ��ꍇ�A�X�V���Ȃ����������
		DX12GameManager::updateUploadBuffer(m_createUploadCameraCbufferHandle, transformBufferData);

		// ���W�ϊ��p�̒萔�o�b�t�@�ɃA�b�v���[�h�o�b�t�@�̏����R�s�[����
		DX12GameManager::copyBuffer(m_createUploadCameraCbufferHandle);
	}

	void MeshDrawFuncRunner::updateShadowMapCbuffer() const
	{
		// ���b�V���̃V���h�E�}�b�v�`��p�萔�o�b�t�@�`��
		MeshShadowMapCBuffer shadowMapBufferData{};

		// �V���h�E�}�b�v���g�p����ׂɕK�v�ȃV���h�E�}�b�v�J�����s��
		shadowMapBufferData.shadowMapViewProjMat = DX12GameManager::getViewMatrix(m_shadowMapCameraHandle) * DX12GameManager::getProjectionMatrix(m_shadowMapCameraHandle);

		// �萔�o�b�t�@�̃A�b�v���[�h�p�o�b�t�@���X�V����
		// TODO : �O�t���[���ƒ萔�o�b�t�@�ɕω����Ȃ��ꍇ�A�X�V���Ȃ����������
		DX12GameManager::updateUploadBuffer(m_createUploadShadowMapCbufferHandle, shadowMapBufferData);

		// �V���h�E�}�b�v�g�p�p�̒萔�o�b�t�@�ɃA�b�v���[�h�p�o�b�t�@�̏����R�s�[����
		DX12GameManager::copyBuffer(m_createUploadShadowMapCbufferHandle);
	}
}