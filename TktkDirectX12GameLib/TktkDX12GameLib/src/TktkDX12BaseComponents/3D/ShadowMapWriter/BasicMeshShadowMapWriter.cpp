#include "TktkDX12BaseComponents/3D/ShadowMapWriter/BasicMeshShadowMapWriter.h"

namespace tktk
{
	BasicMeshShadowMapWriter::BasicMeshShadowMapWriter(float drawPriority, const tktkMath::Vector3& baseScale, const tktkMath::Quaternion& baseRotation, size_t meshHandle, size_t skeletonHandle, size_t cameraHandle)
		: ComponentBase(drawPriority)
		, m_meshHandle(meshHandle)
		, m_skeletonHandle(skeletonHandle)
		, m_cameraHandle(cameraHandle)
		, m_baseScale(baseScale)
		, m_baseRotation(baseRotation)
	{
	}

	void BasicMeshShadowMapWriter::start()
	{
		m_transform = getComponent<Transform3D>();

		if (m_transform.expired())
		{
			throw std::runtime_error("BasicMeshShadowMapWriter not found Transform3D");
		}

		// �A�b�v���[�h�p�o�b�t�@�����A���̃n���h�����擾����
		m_createUploadTransformCbufferHandle = DX12GameManager::createUploadBuffer(UploadBufferInitParam::create(BufferType::constant, DX12GameManager::getSystemHandle(SystemCBufferType::MeshTransform), MeshTransformCbuffer()));
		m_createUploadBoneMatrixCbufferHandle = DX12GameManager::createSkeletonUploadBufferHandle(m_skeletonHandle);
	}

	void BasicMeshShadowMapWriter::onDestroy()
	{
		// �A�b�v���[�h�p�o�b�t�@���폜����
		DX12GameManager::eraseUploadBuffer(m_createUploadTransformCbufferHandle);
		DX12GameManager::eraseUploadBuffer(m_createUploadBoneMatrixCbufferHandle);
	}

	void BasicMeshShadowMapWriter::draw() const
	{
		// �{�[���s��̒萔�o�b�t�@���X�V����
		DX12GameManager::updateBoneMatrixCbuffer(m_skeletonHandle, m_createUploadBoneMatrixCbufferHandle);

		// ���W�ϊ��p�̒萔�o�b�t�@�̍X�V���s��
		updateTransformCbuffer();

		// �V���h�E�}�b�v��`�悷��
		DX12GameManager::writeBasicMeshShadowMap(m_meshHandle);
	}

	void BasicMeshShadowMapWriter::updateTransformCbuffer() const
	{
		// �[�x�}�b�v�����o���ɕK�v�Ȓl
		MeshTransformCbuffer transformBufferData{};

		// Transform3D���烏�[���h�s����擾
		transformBufferData.worldMatrix = tktkMath::Matrix4::createTRS(
			m_transform->getWorldPosition(),
			m_baseRotation * m_transform->getWorldRotation(),
			tktkMath::Vector3::scale(m_baseScale, m_transform->getWorldScaleRate())
		);

		// �g�p����J�����̃r���[�s��
		transformBufferData.viewMatrix = DX12GameManager::getViewMatrix(m_cameraHandle);

		// �g�p����J�����̃v���W�F�N�V�����s��
		transformBufferData.projectionMatrix = DX12GameManager::getProjectionMatrix(m_cameraHandle);

		// �萔�o�b�t�@�̃A�b�v���[�h�p�o�b�t�@���X�V����
		// TODO : �O�t���[���ƒ萔�o�b�t�@�ɕω����Ȃ��ꍇ�A�X�V���Ȃ����������
		DX12GameManager::updateUploadBuffer(m_createUploadTransformCbufferHandle, transformBufferData);

		// ���W�ϊ��p�̒萔�o�b�t�@�ɃA�b�v���[�h�p�o�b�t�@�̏����R�s�[����
		DX12GameManager::copyBuffer(m_createUploadTransformCbufferHandle);
	}
}