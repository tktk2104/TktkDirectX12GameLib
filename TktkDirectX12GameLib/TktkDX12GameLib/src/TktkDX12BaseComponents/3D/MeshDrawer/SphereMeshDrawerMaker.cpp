#include "TktkDX12BaseComponents/3D/MeshDrawer/SphereMeshDrawerMaker.h"

namespace tktk
{
	SphereMeshDrawerMaker SphereMeshDrawerMaker::m_self;

	SphereMeshDrawerMaker& SphereMeshDrawerMaker::makeStart(GameObjectPtr user)
	{
		// �ϐ�������������
		m_self = SphereMeshDrawerMaker();

		// �����̃��[�U�[��ݒ�
		m_self.m_user = user;

		// �g�p����J�����n���h���̃f�t�H���g�l�̓f�t�H���g�ʏ�J����
		m_self.m_useResourceHandles.cameraHandle			= DX12GameManager::getSystemHandle(SystemCameraType::DefaultCamera);

		// �g�p����V���h�E�}�b�v�J�����n���h���̃f�t�H���g�l�̓f�t�H���g�V���h�E�}�b�v�J����
		m_self.m_useResourceHandles.shadowMapCameraHandle	= DX12GameManager::getSystemHandle(SystemCameraType::DefaultShadowMapCamera);

		// �g�p���郌���_�[�^�[�Q�b�g�̃f�B�X�N���v�^�q�[�v�n���h���̃f�t�H���g�l�̓o�b�N�o�b�t�@
		m_self.m_useResourceHandles.rtvDescriptorHeapHandle = DX12GameManager::getSystemHandle(SystemRtvDescriptorHeapType::BackBuffer);

		// ���g�̎Q�Ƃ�Ԃ�
		return m_self;
	}

	ComponentPtr<SphereMeshDrawer> SphereMeshDrawerMaker::create()
	{
		// �R���|�[�l���g���쐬���Ă��̃|�C���^��Ԃ�
		return m_user->createComponent<SphereMeshDrawer>(
			m_drawPriority,
			m_radius,
			m_localPosition,
			m_albedoColor,
			m_useResourceHandles
			);
	}

	SphereMeshDrawerMaker& SphereMeshDrawerMaker::drawPriority(float value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_drawPriority = value;
		return *this;
	}

	SphereMeshDrawerMaker& SphereMeshDrawerMaker::radius(float value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_radius = value;
		return *this;
	}

	SphereMeshDrawerMaker& SphereMeshDrawerMaker::localPosition(const tktkMath::Vector3& value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_localPosition = value;
		return *this;
	}

	SphereMeshDrawerMaker& SphereMeshDrawerMaker::albedoColor(const tktkMath::Color& value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_albedoColor = value;
		return *this;
	}

	SphereMeshDrawerMaker& SphereMeshDrawerMaker::useRtvDescriptorHeapHandle(unsigned int value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_useResourceHandles.rtvDescriptorHeapHandle = value;
		return *this;
	}

	SphereMeshDrawerMaker& SphereMeshDrawerMaker::cameraHandle(unsigned int value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_useResourceHandles.cameraHandle = value;
		return *this;
	}

	SphereMeshDrawerMaker& SphereMeshDrawerMaker::shadowMapCameraHandle(unsigned int value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_useResourceHandles.shadowMapCameraHandle = value;
		return *this;
	}

	SphereMeshDrawerMaker& SphereMeshDrawerMaker::lightHandle(unsigned int value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_useResourceHandles.lightHandle = value;
		return *this;
	}

	SphereMeshDrawerMaker& SphereMeshDrawerMaker::cameraIdImpl(int value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_useResourceHandles.cameraHandle = DX12GameManager::getCameraHandle(value);
		return *this;
	}

	SphereMeshDrawerMaker& SphereMeshDrawerMaker::shadowMapCameraIdImpl(int value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_useResourceHandles.shadowMapCameraHandle = DX12GameManager::getCameraHandle(value);
		return *this;
	}

	SphereMeshDrawerMaker& SphereMeshDrawerMaker::lightIdImpl(int value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_useResourceHandles.lightHandle = DX12GameManager::getLightHandle(value);
		return *this;
	}
}