#include "TktkDX12BaseComponents/3D/MeshDrawer/SphereMeshWireFrameDrawer.h"

#include "TktkDX12Game/DXGameResource/Mesh/BasicMesh/Structs/BasicMonoColorMeshCbuffer.h"

namespace tktk
{
	SphereMeshWireFrameDrawer::SphereMeshWireFrameDrawer(float drawPriority, float radius, const tktkMath::Vector3& localPosition, const tktkMath::Color& albedoColor, const SphereMeshDrawerUseResourceHandles& useResourceHandles)
		: ComponentBase(drawPriority)
		, m_radius(radius)
		, m_localPosition(localPosition)
		, m_albedoColor(albedoColor)
		, m_useResourceHandles(useResourceHandles)
	{
	}

	void SphereMeshWireFrameDrawer::start()
	{
		m_transform = getComponent<Transform3D>();

		if (m_transform.expired())
		{
			throw std::runtime_error("BasicMeshDrawer not found Transform3D");
		}
		// �A�b�v���[�h�p�o�b�t�@�����A���̃n���h�����擾����
		m_createUploadTransformCbufferHandle		= DX12GameManager::createUploadBuffer(UploadBufferInitParam::create(BufferType::constant, DX12GameManager::getSystemHandle(SystemCBufferType::MeshTransform), MeshTransformCbuffer()));
		m_createUploadShadowMapCbufferHandle		= DX12GameManager::createUploadBuffer(UploadBufferInitParam::create(BufferType::constant, DX12GameManager::getSystemHandle(SystemCBufferType::MeshShadowMap), MeshShadowMapCBuffer()));
		m_createUploadMonoColorMeshCbufferHandle	= DX12GameManager::createUploadBuffer(UploadBufferInitParam::create(BufferType::constant, DX12GameManager::getSystemHandle(SystemCBufferType::BasicMonoColorMeshCbuffer), BasicMonoColorMeshCbuffer()));
	}

	void SphereMeshWireFrameDrawer::onDestroy()
	{
		// �A�b�v���[�h�p�o�b�t�@���폜����
		DX12GameManager::eraseUploadBuffer(m_createUploadTransformCbufferHandle);
		DX12GameManager::eraseUploadBuffer(m_createUploadShadowMapCbufferHandle);
		DX12GameManager::eraseUploadBuffer(m_createUploadMonoColorMeshCbufferHandle);
	}

	void SphereMeshWireFrameDrawer::draw() const
	{
		// �{�[�����̒萔�o�b�t�@��P�ʍs��ŏ�����
		DX12GameManager::resetBoneMatrixCbuffer();

		// �P�F�h��Ԃ��F�̒萔�o�b�t�@���X�V����
		{
			BasicMonoColorMeshCbuffer tempCbufferData{};
			tempCbufferData.albedoColor = m_albedoColor;

			DX12GameManager::updateUploadBuffer(m_createUploadMonoColorMeshCbufferHandle, tempCbufferData);
			DX12GameManager::copyBuffer(m_createUploadMonoColorMeshCbufferHandle);
		}

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
		DX12GameManager::drawBasicMesh(DX12GameManager::getSystemHandle(SystemBasicMeshType::SphereWireFrame), baseArgs);
	}

	const tktkMath::Color& SphereMeshWireFrameDrawer::getAlbedoColor() const
	{
		return m_albedoColor;
	}

	void SphereMeshWireFrameDrawer::updateTransformCbuffer() const
	{
		// ���b�V���̍��W�ϊ��p�萔�o�b�t�@�`��
		MeshTransformCbuffer transformBufferData{};

		// Transform3D���烏�[���h�s����擾
		transformBufferData.worldMatrix = tktkMath::Matrix4::createTranslation(m_localPosition) * m_transform->calculateWorldMatrix();

		// �g�p����J�����̃r���[�s��
		transformBufferData.viewMatrix = DX12GameManager::getViewMatrix(m_useResourceHandles.cameraHandle);

		// �g�p����J�����̃v���W�F�N�V�����s��
		transformBufferData.projectionMatrix = DX12GameManager::getProjectionMatrix(m_useResourceHandles.cameraHandle);

		// �萔�o�b�t�@�̃A�b�v���[�h�p�o�b�t�@���X�V����
		// TODO : �O�t���[���ƒ萔�o�b�t�@�ɕω����Ȃ��ꍇ�A�X�V���Ȃ����������
		DX12GameManager::updateUploadBuffer(m_createUploadTransformCbufferHandle, transformBufferData);

		// ���W�ϊ��p�̒萔�o�b�t�@�ɃA�b�v���[�h�p�o�b�t�@�̏����R�s�[����
		DX12GameManager::copyBuffer(m_createUploadTransformCbufferHandle);
	}

	void SphereMeshWireFrameDrawer::updateShadowMapCbuffer() const
	{
		// ���b�V���̃V���h�E�}�b�v�`��p�萔�o�b�t�@�`��
		MeshShadowMapCBuffer shadowMapBufferData{};

		// �V���h�E�}�b�v���g�p����ׂɕK�v�ȃV���h�E�}�b�v�J�����s��
		shadowMapBufferData.shadowMapViewProjMat = DX12GameManager::getViewMatrix(m_useResourceHandles.shadowMapCameraHandle) * DX12GameManager::getProjectionMatrix(m_useResourceHandles.shadowMapCameraHandle);

		// �萔�o�b�t�@�̃A�b�v���[�h�p�o�b�t�@���X�V����
		// TODO : �O�t���[���ƒ萔�o�b�t�@�ɕω����Ȃ��ꍇ�A�X�V���Ȃ����������
		DX12GameManager::updateUploadBuffer(m_createUploadShadowMapCbufferHandle, shadowMapBufferData);

		// �V���h�E�}�b�v�g�p�p�̒萔�o�b�t�@�ɃA�b�v���[�h�p�o�b�t�@�̏����R�s�[����
		DX12GameManager::copyBuffer(m_createUploadShadowMapCbufferHandle);
	}
}