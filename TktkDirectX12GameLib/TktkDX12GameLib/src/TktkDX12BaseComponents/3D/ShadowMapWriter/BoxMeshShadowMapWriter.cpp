#include "TktkDX12BaseComponents/3D/ShadowMapWriter/BoxMeshShadowMapWriter.h"

namespace tktk
{
	BoxMeshShadowMapWriter::BoxMeshShadowMapWriter(float drawPriority, const tktkMath::Vector3& boxSize, const tktkMath::Vector3& localPosition, unsigned int cameraHandle)
		: ComponentBase(drawPriority)
		, m_boxSize(boxSize)
		, m_localPosition(localPosition)
		, m_cameraHandle(cameraHandle)
	{
	}

	void BoxMeshShadowMapWriter::start()
	{
		m_transform = getComponent<Transform3D>();

		if (m_transform.expired())
		{
			throw std::runtime_error("BoxMeshShadowMapWriter not found Transform3D");
		}

		// �R�s�[�p�o�b�t�@�����A���̃n���h�����擾����
		m_createCopyTransformCbufferHandle = DX12GameManager::createCopyBuffer(BufferType::constant, DX12GameManager::getSystemHandle(SystemCBufferType::MeshTransform), MeshTransformCbuffer());
	}

	void BoxMeshShadowMapWriter::onDestroy()
	{
		// �R�s�[�p�o�b�t�@���폜����
		DX12GameManager::eraseCopyBuffer(m_createCopyTransformCbufferHandle);
	}

	void BoxMeshShadowMapWriter::draw() const
	{
		// �{�[�����̒萔�o�b�t�@��P�ʍs��ŏ�����
		DX12GameManager::resetBoneMatrixCbuffer();

		// ���W�ϊ��p�̒萔�o�b�t�@�̍X�V���s��
		updateTransformCbuffer();

		// �V���h�E�}�b�v��`�悷��
		DX12GameManager::writeBasicMeshShadowMap(DX12GameManager::getSystemHandle(SystemBasicMeshType::Box));
	}

	void BoxMeshShadowMapWriter::updateTransformCbuffer() const
	{
		// ���b�V���̍��W�ϊ��p�萔�o�b�t�@�`��
		MeshTransformCbuffer transformBufferData{};

		// Transform3D���烏�[���h�s����擾
		transformBufferData.worldMatrix = tktkMath::Matrix4::createTRS(
			m_localPosition + m_transform->getWorldPosition(),
			m_transform->getWorldRotation(),
			tktkMath::Vector3::scale(m_boxSize * 0.5f, m_transform->getWorldScaleRate())
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