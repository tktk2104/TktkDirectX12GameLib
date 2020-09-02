#include "TktkDX12BaseComponents/3D/MeshDrawer/SphereMeshDrawer.h"

#include "TktkDX12Game/DXGameResource/Mesh/BasicMesh/Structs/BasicMonoColorMeshCbuffer.h"

namespace tktk
{
	SphereMeshDrawer::SphereMeshDrawer(float drawPriority, float radius, const tktkMath::Vector3& localPosition, const tktkMath::Color& albedoColor, const SphereMeshDrawerUseResourceHandles& useResourceHandles)
		: ComponentBase(drawPriority)
		, m_radius(radius)
		, m_localPosition(localPosition)
		, m_albedoColor(albedoColor)
		, m_useResourceHandles(useResourceHandles)
	{
	}

	void SphereMeshDrawer::start()
	{
		m_transform = getComponent<Transform3D>();

		if (m_transform.expired())
		{
			throw std::runtime_error("BasicMeshDrawer not found Transform3D");
		}

		// �R�s�[�p�o�b�t�@�����A���̃n���h�����擾����
		m_createCopyTransformCbufferHandle = DX12GameManager::createCopyBuffer(BufferType::constant, DX12GameManager::getSystemHandle(SystemCBufferType::MeshTransform), MeshTransformCbuffer());
		m_createCopyShadowMapCbufferHandle = DX12GameManager::createCopyBuffer(BufferType::constant, DX12GameManager::getSystemHandle(SystemCBufferType::MeshShadowMap), MeshShadowMapCBuffer());
	}

	void SphereMeshDrawer::onDestroy()
	{
		// �R�s�[�p�o�b�t�@���폜����
		DX12GameManager::eraseCopyBuffer(m_createCopyTransformCbufferHandle);
		DX12GameManager::eraseCopyBuffer(m_createCopyShadowMapCbufferHandle);
	}

	void SphereMeshDrawer::draw() const
	{
		// �{�[�����̒萔�o�b�t�@��P�ʍs��ŏ�����
		DX12GameManager::resetBoneMatrixCbuffer();

		// �P�F�h��Ԃ��F�̒萔�o�b�t�@���X�V����
		BasicMonoColorMeshCbuffer tempCbufferData{};
		tempCbufferData.albedoColor = m_albedoColor;
		DX12GameManager::updateMaterialAppendParam(DX12GameManager::getSystemHandle(SystemBasicMeshMaterialType::Sphere), DX12GameManager::getSystemHandle(SystemCBufferType::BasicMonoColorMeshCbuffer), tempCbufferData);

		// ���W�ϊ��p�̒萔�o�b�t�@�̍X�V���s��
		updateTransformCbuffer();

		// �V���h�E�}�b�v�p�̒萔�o�b�t�@�̍X�V���s��
		updateShadowMapCbuffer();

		// ���b�V���`��ɕK�v�Ȓl
		MeshDrawFuncBaseArgs baseArgs{};

		// �g�p����r���[�|�[�g�n���h��
		baseArgs.viewportHandle = DX12GameManager::getSystemHandle(SystemViewportType::Basic);

		// �g�p����V�U�[��`�n���h��
		baseArgs.scissorRectHandle = DX12GameManager::getSystemHandle(SystemScissorRectType::Basic);

		// �g�p���郌���_�[�^�[�Q�b�g�f�B�X�N���v�^�q�[�v�n���h��
		baseArgs.rtvDescriptorHeapHandle = m_useResourceHandles.rtvDescriptorHeapHandle;

		// �g�p����[�x�X�e���V���f�B�X�N���v�^�q�[�v�n���h��
		baseArgs.dsvDescriptorHeapHandle = DX12GameManager::getSystemHandle(SystemDsvDescriptorHeapType::Basic);

		// �g�p���郉�C�g�ԍ�
		baseArgs.lightHandle = m_useResourceHandles.lightHandle;

		// ���b�V����`�悷��
		DX12GameManager::drawBasicMesh(DX12GameManager::getSystemHandle(SystemBasicMeshType::Sphere), baseArgs);
	}

	const tktkMath::Color& SphereMeshDrawer::getAlbedoColor() const
	{
		return m_albedoColor;
	}

	void SphereMeshDrawer::setAlbedoColor(const tktkMath::Color& color)
	{
		m_albedoColor = color;
	}

	void SphereMeshDrawer::updateTransformCbuffer() const
	{
		// ���b�V���̍��W�ϊ��p�萔�o�b�t�@�`��
		MeshTransformCbuffer transformBufferData{};

		// Transform3D���烏�[���h�s����擾
		transformBufferData.worldMatrix = m_transform->calculateWorldMatrix();

		// �g�p����J�����̃r���[�s��
		transformBufferData.viewMatrix = DX12GameManager::getViewMatrix(m_useResourceHandles.cameraHandle);

		// �g�p����J�����̃v���W�F�N�V�����s��
		transformBufferData.projectionMatrix = DX12GameManager::getProjectionMatrix(m_useResourceHandles.cameraHandle);

		// �萔�o�b�t�@�̃R�s�[�p�o�b�t�@���X�V����
		// TODO : �O�t���[���ƒ萔�o�b�t�@�ɕω����Ȃ��ꍇ�A�X�V���Ȃ����������
		DX12GameManager::updateCopyBuffer(m_createCopyTransformCbufferHandle, transformBufferData);

		// ���W�ϊ��p�̒萔�o�b�t�@�ɃR�s�[�o�b�t�@�̏����R�s�[����
		DX12GameManager::copyBuffer(m_createCopyTransformCbufferHandle);
	}

	void SphereMeshDrawer::updateShadowMapCbuffer() const
	{
		// ���b�V���̃V���h�E�}�b�v�`��p�萔�o�b�t�@�`��
		MeshShadowMapCBuffer shadowMapBufferData{};

		// �V���h�E�}�b�v���g�p����ׂɕK�v�ȃV���h�E�}�b�v�J�����s��
		shadowMapBufferData.shadowMapViewProjMat = DX12GameManager::getViewMatrix(m_useResourceHandles.shadowMapCameraHandle) * DX12GameManager::getProjectionMatrix(m_useResourceHandles.shadowMapCameraHandle);

		// �萔�o�b�t�@�̃R�s�[�p�o�b�t�@���X�V����
		// TODO : �O�t���[���ƒ萔�o�b�t�@�ɕω����Ȃ��ꍇ�A�X�V���Ȃ����������
		DX12GameManager::updateCopyBuffer(m_createCopyShadowMapCbufferHandle, shadowMapBufferData);

		// �V���h�E�}�b�v�g�p�p�̒萔�o�b�t�@�ɃR�s�[�o�b�t�@�̏����R�s�[����
		DX12GameManager::copyBuffer(m_createCopyShadowMapCbufferHandle);
	}
}