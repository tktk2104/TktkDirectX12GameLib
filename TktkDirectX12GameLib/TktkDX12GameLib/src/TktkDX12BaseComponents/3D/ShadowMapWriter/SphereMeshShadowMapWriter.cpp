#include "TktkDX12BaseComponents/3D/ShadowMapWriter/SphereMeshShadowMapWriter.h"

namespace tktk
{
	SphereMeshShadowMapWriter::SphereMeshShadowMapWriter(float drawPriority, float radius, const tktkMath::Vector3& localPosition, size_t cameraHandle)
		: ComponentBase(drawPriority)
		, m_radius(radius)
		, m_localPosition(localPosition)
		, m_cameraHandle(cameraHandle)
	{
	}

	void SphereMeshShadowMapWriter::start()
	{
		m_transform = getComponent<Transform3D>();

		if (m_transform.expired())
		{
			throw std::runtime_error("SphereMeshShadowMapWriter not found Transform3D");
		}

		// �A�b�v���[�h�p�o�b�t�@�����A���̃n���h�����擾����
		m_createUploadTransformCbufferHandle = DX12GameManager::createUploadBuffer(UploadBufferInitParam::create(BufferType::constant, DX12GameManager::getSystemHandle(SystemCBufferType::MeshTransform), MeshTransformCbuffer()));
	}

	void SphereMeshShadowMapWriter::onDestroy()
	{
		// �A�b�v���[�h�p�o�b�t�@���폜����
		DX12GameManager::eraseUploadBuffer(m_createUploadTransformCbufferHandle);
	}

	void SphereMeshShadowMapWriter::draw() const
	{
		// �{�[�����̒萔�o�b�t�@��P�ʍs��ŏ�����
		DX12GameManager::resetBoneMatrixCbuffer();

		// ���W�ϊ��p�̒萔�o�b�t�@�̍X�V���s��
		updateTransformCbuffer();

		// �V���h�E�}�b�v��`�悷��
		DX12GameManager::writeBasicMeshShadowMap(DX12GameManager::getSystemHandle(SystemBasicMeshType::Sphere));
	}

	void SphereMeshShadowMapWriter::updateTransformCbuffer() const
	{
		// ���b�V���̍��W�ϊ��p�萔�o�b�t�@�`��
		MeshTransformCbuffer transformBufferData{};

		// Transform3D���烏�[���h�s����擾
		transformBufferData.worldMatrix = m_transform->calculateWorldMatrix();

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