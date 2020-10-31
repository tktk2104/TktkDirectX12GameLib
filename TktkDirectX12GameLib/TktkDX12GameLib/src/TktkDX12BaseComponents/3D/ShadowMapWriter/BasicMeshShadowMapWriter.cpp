#include "TktkDX12BaseComponents/3D/ShadowMapWriter/BasicMeshShadowMapWriter.h"

namespace tktk
{
	BasicMeshShadowMapWriter::BasicMeshShadowMapWriter(float drawPriority, const tktkMath::Vector3& baseScale, const tktkMath::Quaternion& baseRotation, unsigned int meshHandle, unsigned int skeletonHandle, unsigned int cameraHandle)
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

		// �R�s�[�p�o�b�t�@�����A���̃n���h�����擾����
		m_createCopyTransformCbufferHandle = DX12GameManager::createCopyBuffer(BufferType::constant, DX12GameManager::getSystemHandle(SystemCBufferType::MeshTransform), MeshTransformCbuffer());
		m_createCopyBoneMatrixCbufferHandle = DX12GameManager::createSkeletonCopyBufferHandle(m_skeletonHandle);
	}

	void BasicMeshShadowMapWriter::onDestroy()
	{
		// �R�s�[�p�o�b�t�@���폜����
		DX12GameManager::eraseCopyBuffer(m_createCopyTransformCbufferHandle);
		DX12GameManager::eraseCopyBuffer(m_createCopyBoneMatrixCbufferHandle);
	}

	void BasicMeshShadowMapWriter::draw() const
	{
		// �{�[���s��̒萔�o�b�t�@���X�V����
		DX12GameManager::updateBoneMatrixCbuffer(m_skeletonHandle, m_createCopyBoneMatrixCbufferHandle);

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

		// �萔�o�b�t�@�̃R�s�[�p�o�b�t�@���X�V����
		// TODO : �O�t���[���ƒ萔�o�b�t�@�ɕω����Ȃ��ꍇ�A�X�V���Ȃ����������
		DX12GameManager::updateCopyBuffer(m_createCopyTransformCbufferHandle, transformBufferData);

		// ���W�ϊ��p�̒萔�o�b�t�@�ɃR�s�[�o�b�t�@�̏����R�s�[����
		DX12GameManager::copyBuffer(m_createCopyTransformCbufferHandle);
	}
}