#include "TktkDX12BaseComponents/3D/MeshDrawer/BoxMeshDrawer.h"

#include "TktkDX12BaseComponents/3D/Transform3D/Transform3D.h"
#include "TktkDX12Game/_MainManager/DX12GameManager.h"
#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/MeshResouse/Mesh/Structs/MeshTransformCbuffer.h"
#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/MeshResouse/Mesh/Structs/MeshShadowMapCBuffer.h"
#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/MeshResouse/MeshMaterial/Structs/MonoColorMeshCbuffer.h"

namespace tktk
{
	BoxMeshDrawer::BoxMeshDrawer(float drawPriority, const tktkMath::Vector3& boxSize, const tktkMath::Vector3& localPosition, const tktkMath::Color& albedoColor, const BoxMeshDrawerUseResourceHandles& useResourceHandles)
		: ComponentBase(drawPriority)
		, m_boxSize(boxSize)
		, m_localPosition(localPosition)
		, m_albedoColor(albedoColor)
		, m_useResourceHandles(useResourceHandles)
	{
	}

	void BoxMeshDrawer::start()
	{
		m_transform = getComponent<Transform3D>();

		if (m_transform.expired())
		{
			throw std::runtime_error("BasicMeshDrawer not found Transform3D");
		}

		// �R�s�[�p�o�b�t�@�����A���̃n���h�����擾����
		m_createUploadTransformCbufferHandle		= DX12GameManager::createUploadBuffer(UploadBufferInitParam::create(BufferType::constant, DX12GameManager::getSystemHandle(SystemCBufferType::MeshTransform), MeshTransformCbuffer()));
		m_createUploadShadowMapCbufferHandle		= DX12GameManager::createUploadBuffer(UploadBufferInitParam::create(BufferType::constant, DX12GameManager::getSystemHandle(SystemCBufferType::MeshShadowMap), MeshShadowMapCBuffer()));
		m_createUploadMonoColorMeshCbufferHandle	= DX12GameManager::createUploadBuffer(UploadBufferInitParam::create(BufferType::constant, DX12GameManager::getSystemHandle(SystemCBufferType::BasicMonoColorMeshCbuffer), MonoColorMeshCbuffer()));
	}

	void BoxMeshDrawer::onDestroy()
	{
		// �A�b�v���[�h�p�o�b�t�@���폜����
		DX12GameManager::eraseUploadBuffer(m_createUploadTransformCbufferHandle);
		DX12GameManager::eraseUploadBuffer(m_createUploadShadowMapCbufferHandle);
		DX12GameManager::eraseUploadBuffer(m_createUploadMonoColorMeshCbufferHandle);
	}

	void BoxMeshDrawer::draw() const
	{
		// �{�[�����̒萔�o�b�t�@��P�ʍs��ŏ�����
		DX12GameManager::resetBoneMatrixCbuffer();

		// �P�F�h��Ԃ��F�̒萔�o�b�t�@���X�V����
		{
			MonoColorMeshCbuffer tempCbufferData{};
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
		DX12GameManager::drawMesh(DX12GameManager::getSystemHandle(SystemBasicMeshType::Box), baseArgs);
	}

	const tktkMath::Color& BoxMeshDrawer::getAlbedoColor() const
	{
		return m_albedoColor;
	}

	void BoxMeshDrawer::setAlbedoColor(const tktkMath::Color& color)
	{
		m_albedoColor = color;
	}

	void BoxMeshDrawer::updateTransformCbuffer() const
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
		transformBufferData.viewMatrix = DX12GameManager::getViewMatrix(m_useResourceHandles.cameraHandle);

		// �g�p����J�����̃v���W�F�N�V�����s��
		transformBufferData.projectionMatrix = DX12GameManager::getProjectionMatrix(m_useResourceHandles.cameraHandle);

		// �萔�o�b�t�@�̃A�b�v���[�h�p�o�b�t�@���X�V����
		// TODO : �O�t���[���ƒ萔�o�b�t�@�ɕω����Ȃ��ꍇ�A�X�V���Ȃ����������
		DX12GameManager::updateUploadBuffer(m_createUploadTransformCbufferHandle, transformBufferData);

		// ���W�ϊ��p�̒萔�o�b�t�@�ɃA�b�v���[�h�o�b�t�@�̏����R�s�[����
		DX12GameManager::copyBuffer(m_createUploadTransformCbufferHandle);
	}

	void BoxMeshDrawer::updateShadowMapCbuffer() const
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