#include "TktkDX12BaseComponents/3D/ShadowMapWriter/WriteMeshShadowMapFuncRunner.h"

#include "TktkDX12Game/_MainManager/DX12GameManager.h"
#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/MeshResouse/Mesh/Structs/CameraCbuffer.h"

namespace tktk
{
	WriteMeshShadowMapFuncRunner::WriteMeshShadowMapFuncRunner(size_t meshHandle, bool useBone)
		: ComponentBase(-1000.0f)
		, m_meshHandle(meshHandle)
		, m_useBone(useBone)
	{
	}

	void WriteMeshShadowMapFuncRunner::start()
	{
		// �A�b�v���[�h�p�o�b�t�@�����A���̃n���h�����擾����
		m_createUploadCameraCbufferHandle = DX12GameManager::createUploadBuffer(UploadBufferInitParam::create(BufferType::constant, DX12GameManager::getSystemHandle(SystemCBufferType::Camera), CameraCbuffer()));
	}

	void WriteMeshShadowMapFuncRunner::onDestroy()
	{
		// �A�b�v���[�h�p�o�b�t�@���폜����
		DX12GameManager::eraseUploadBuffer(m_createUploadCameraCbufferHandle);
	}

	void WriteMeshShadowMapFuncRunner::draw() const
	{
		// �J�������萔�o�b�t�@�̍X�V
		updateCameraCbuffer();

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