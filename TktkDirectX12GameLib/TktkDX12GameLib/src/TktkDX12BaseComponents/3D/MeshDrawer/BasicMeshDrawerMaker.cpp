#include "TktkDX12BaseComponents/3D/MeshDrawer/BasicMeshDrawerMaker.h"

namespace tktk
{
	BasicMeshDrawerMaker BasicMeshDrawerMaker::m_self;

	BasicMeshDrawerMaker& BasicMeshDrawerMaker::makeStart(GameObjectPtr user)
	{
		// �ϐ�������������
		m_self = BasicMeshDrawerMaker();

		// �����̃��[�U�[��ݒ�
		m_self.m_user = user;

		// �g�p����J�����n���h���̃f�t�H���g�l�̓f�t�H���g�ʏ�J����
		m_self.m_useResourceHandles.cameraHandle			= DX12GameManager::getSystemHandle(SystemCameraType::DefaultCamera);

		// �g�p����V���h�E�}�b�v�J�����n���h���̃f�t�H���g�l�̓f�t�H���g�V���h�E�}�b�v�J����
		m_self.m_useResourceHandles.shadowMapCameraHandle	= DX12GameManager::getSystemHandle(SystemCameraType::DefaultShadowMapCamera);

		// �g�p���郉�C�g�n���h���̃f�t�H���g�l�̓f�t�H���g���C�g
		m_self.m_useResourceHandles.lightHandle				= DX12GameManager::getSystemHandle(SystemLightType::DefaultLight);

		// �g�p���郌���_�[�^�[�Q�b�g�̃f�B�X�N���v�^�q�[�v�n���h���̃f�t�H���g�l�̓o�b�N�o�b�t�@
		m_self.m_useResourceHandles.rtvDescriptorHeapHandle = DX12GameManager::getSystemHandle(SystemRtvDescriptorHeapType::BackBuffer);

		// ���g�̎Q�Ƃ�Ԃ�
		return m_self;
	}

	ComponentPtr<BasicMeshDrawer> BasicMeshDrawerMaker::create()
	{
		// ���g��ǉ�����K�w��񂪋󂾂����畁�ʂɍ쐬����
		if (m_targetState.empty())
		{
			// �R���|�[�l���g���쐬���Ă��̃|�C���^��Ԃ�
			return m_user->createComponent<BasicMeshDrawer>(m_drawPriority, m_baseScale, m_baseRotation, m_useResourceHandles);
		}
		
		// �R���|�[�l���g���쐬����
		auto createComponent = m_user->createComponent<BasicMeshDrawer>(m_drawPriority, m_baseScale, m_baseRotation, m_useResourceHandles);

		// �쐬�����R���|�[�l���g�����̃X�e�[�g�ɒǉ�����
		m_user->setComponentToStateMachine(m_targetState, createComponent);

		// �쐬�����R���|�[�l���g�̃|�C���^��Ԃ�
		return createComponent;
	}

	BasicMeshDrawerMaker& BasicMeshDrawerMaker::drawPriority(float value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_drawPriority = value;
		return *this;
	}

	BasicMeshDrawerMaker& BasicMeshDrawerMaker::baseScale(const tktkMath::Vector3& value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_baseScale = value;
		return *this;
	}

	BasicMeshDrawerMaker& BasicMeshDrawerMaker::baseRotation(const tktkMath::Quaternion& value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_baseRotation = value;
		return *this;
	}

	BasicMeshDrawerMaker& BasicMeshDrawerMaker::useRtvDescriptorHeapHandle(unsigned int value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_useResourceHandles.rtvDescriptorHeapHandle = value;
		return *this;
	}

	BasicMeshDrawerMaker& BasicMeshDrawerMaker::meshHandle(unsigned int value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_useResourceHandles.meshHandle = value;
		return *this;
	}

	BasicMeshDrawerMaker& BasicMeshDrawerMaker::skeletonHandle(unsigned int value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_useResourceHandles.skeletonHandle = value;
		return *this;
	}

	BasicMeshDrawerMaker& BasicMeshDrawerMaker::cameraHandle(unsigned int value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_useResourceHandles.cameraHandle = value;
		return *this;
	}

	BasicMeshDrawerMaker& BasicMeshDrawerMaker::shadowMapCameraHandle(unsigned int value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_useResourceHandles.shadowMapCameraHandle = value;
		return *this;
	}

	BasicMeshDrawerMaker& BasicMeshDrawerMaker::lightHandle(unsigned int value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_useResourceHandles.lightHandle = value;
		return *this;
	}

	BasicMeshDrawerMaker& BasicMeshDrawerMaker::meshIdImpl(int value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_useResourceHandles.meshHandle = DX12GameManager::getBasicMeshHandle(value);
		return *this;
	}

	BasicMeshDrawerMaker& BasicMeshDrawerMaker::skeletonIdImpl(int value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_useResourceHandles.skeletonHandle = DX12GameManager::getSkeletonHandle(value);
		return *this;
	}

	BasicMeshDrawerMaker& BasicMeshDrawerMaker::cameraIdImpl(int value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_useResourceHandles.cameraHandle = DX12GameManager::getCameraHandle(value);
		return *this;
	}

	BasicMeshDrawerMaker& BasicMeshDrawerMaker::shadowMapCameraIdImpl(int value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_useResourceHandles.shadowMapCameraHandle = DX12GameManager::getCameraHandle(value);
		return *this;
	}

	BasicMeshDrawerMaker& BasicMeshDrawerMaker::lightIdImpl(int value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_useResourceHandles.lightHandle = DX12GameManager::getLightHandle(value);
		return *this;
	}
}