#include "TktkDX12BaseComponents/3D/ShadowMapWriter/BasicMeshShadowMapWriter.h"

namespace tktk
{
	BasicMeshShadowMapWriter::BasicMeshShadowMapWriter(float drawPriority, unsigned int meshHandle, unsigned int skeletonHandle, unsigned int cameraHandle)
		: ComponentBase(drawPriority)
		, m_meshHandle(meshHandle)
		, m_skeletonHandle(skeletonHandle)
		, m_cameraHandle(cameraHandle)
	{
	}

	void BasicMeshShadowMapWriter::start()
	{
		m_transform = getComponent<Transform3D>();

		if (m_transform.expired())
		{
			throw std::runtime_error("BasicMeshShadowMapWriter not found Transform3D");
		}
	}

	void BasicMeshShadowMapWriter::draw() const
	{
		// �{�[���s��̒萔�o�b�t�@���X�V����
		DX12GameManager::updateBoneMatrixCbuffer(m_skeletonHandle);

		// �[�x�}�b�v�����o���ɕK�v�Ȓl
		MeshTransformCbuffer transformBufferData{};
		{
			// Transform3D���烏�[���h�s����擾
			transformBufferData.worldMatrix			= m_transform->calculateWorldMatrix();

			// �g�p����J�����̃r���[�s��
			transformBufferData.viewMatrix			= DX12GameManager::getViewMatrix(m_cameraHandle);

			// �g�p����J�����̃v���W�F�N�V�����s��
			transformBufferData.projectionMatrix	= DX12GameManager::getProjectionMatrix(m_cameraHandle);
		}

		// �V���h�E�}�b�v��`�悷��
		DX12GameManager::writeBasicMeshShadowMap(m_meshHandle, transformBufferData);
	}
}