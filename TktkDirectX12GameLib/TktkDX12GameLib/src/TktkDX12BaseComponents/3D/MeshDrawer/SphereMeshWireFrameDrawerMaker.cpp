#include "TktkDX12BaseComponents/3D/MeshDrawer/SphereMeshWireFrameDrawerMaker.h"

#include "TktkDX12Game/_MainManager/DX12GameManager.h"
#include "TktkDX12Game/DXGameResource/GameObjectResouse/GameObject/GameObject.h"

namespace tktk
{
	SphereMeshWireFrameDrawerMaker SphereMeshWireFrameDrawerMaker::m_self;

	SphereMeshWireFrameDrawerMaker& SphereMeshWireFrameDrawerMaker::makeStart(GameObjectPtr user)
	{
		// �ϐ�������������
		m_self = SphereMeshWireFrameDrawerMaker();

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

	ComponentPtr<SphereMeshWireFrameDrawer> SphereMeshWireFrameDrawerMaker::create()
	{
		// �R���|�[�l���g���쐬����
		return m_user->createComponent<SphereMeshWireFrameDrawer>(
			m_drawPriority,
			m_radius,
			m_localPosition,
			m_albedoColor,
			m_useResourceHandles
			);
	}

	SphereMeshWireFrameDrawerMaker& SphereMeshWireFrameDrawerMaker::drawPriority(float value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_drawPriority = value;
		return *this;
	}

	SphereMeshWireFrameDrawerMaker& SphereMeshWireFrameDrawerMaker::radius(float value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_radius = value;
		return *this;
	}

	SphereMeshWireFrameDrawerMaker& SphereMeshWireFrameDrawerMaker::localPosition(const tktkMath::Vector3& value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_localPosition = value;
		return *this;
	}

	SphereMeshWireFrameDrawerMaker& SphereMeshWireFrameDrawerMaker::albedoColor(const tktkMath::Color& value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_albedoColor = value;
		return *this;
	}

	SphereMeshWireFrameDrawerMaker& SphereMeshWireFrameDrawerMaker::useRtvDescriptorHeapHandle(size_t value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_useResourceHandles.rtvDescriptorHeapHandle = value;
		return *this;
	}

	SphereMeshWireFrameDrawerMaker& SphereMeshWireFrameDrawerMaker::cameraHandle(size_t value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_useResourceHandles.cameraHandle = value;
		return *this;
	}

	SphereMeshWireFrameDrawerMaker& SphereMeshWireFrameDrawerMaker::cameraId(ResourceIdCarrier value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_useResourceHandles.cameraHandle = DX12GameManager::getCameraHandle(value);
		return *this;
	}

	SphereMeshWireFrameDrawerMaker& SphereMeshWireFrameDrawerMaker::shadowMapCameraHandle(size_t value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_useResourceHandles.shadowMapCameraHandle = value;
		return *this;
	}

	SphereMeshWireFrameDrawerMaker& SphereMeshWireFrameDrawerMaker::shadowMapCameraId(ResourceIdCarrier value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_useResourceHandles.shadowMapCameraHandle = DX12GameManager::getCameraHandle(value);
		return *this;
	}

	SphereMeshWireFrameDrawerMaker& SphereMeshWireFrameDrawerMaker::lightHandle(size_t value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_useResourceHandles.lightHandle = value;
		return *this;
	}

	SphereMeshWireFrameDrawerMaker& SphereMeshWireFrameDrawerMaker::lightId(ResourceIdCarrier value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_useResourceHandles.lightHandle = DX12GameManager::getLightHandle(value);
		return *this;
	}
}