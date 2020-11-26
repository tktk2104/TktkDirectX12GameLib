#include "TktkDX12BaseComponents/3D/Camera/ShadowMapCameraControllerMaker.h"

#include "TktkDX12Game/_MainManager/DX12GameManager.h"
#include "TktkDX12Game/DXGameResource/GameObjectResouse/GameObject/GameObject.h"

namespace tktk
{
	ShadowMapCameraControllerMaker ShadowMapCameraControllerMaker::m_self;

	ShadowMapCameraControllerMaker& ShadowMapCameraControllerMaker::makeStart(GameObjectPtr user)
	{
		// �ϐ�������������
		m_self = ShadowMapCameraControllerMaker();

		// �����̃��[�U�[��ݒ�
		m_self.m_user = user;

		// �g�p����J�����n���h���̃f�t�H���g�l�̓f�t�H���g�V���h�E�}�b�v�J����
		m_self.m_initCameraHandle = DX12GameManager::getSystemHandle(SystemCameraType::DefaultShadowMapCamera);

		// ���g�̎Q�Ƃ�Ԃ�
		return m_self;
	}

	ComponentPtr<ShadowMapCameraController> ShadowMapCameraControllerMaker::create()
	{
		return m_user->createComponent<ShadowMapCameraController>(
			m_initCameraHandle,
			m_targetTag,
			m_direction,
			m_initCameraWidth,
			m_initCameraHeight,
			m_initCameraNear,
			m_initCameraFar
			);
	}

	ShadowMapCameraControllerMaker& ShadowMapCameraControllerMaker::initCameraHandle(size_t value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_initCameraHandle = value;
		return *this;
	}

	ShadowMapCameraControllerMaker& ShadowMapCameraControllerMaker::initCameraId(ResourceIdCarrier value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_initCameraHandle = DX12GameManager::getCameraHandle(value);
		return *this;
	}

	ShadowMapCameraControllerMaker& ShadowMapCameraControllerMaker::targetTag(GameObjectTagCarrier value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_targetTag = value;
		return *this;
	}

	ShadowMapCameraControllerMaker& ShadowMapCameraControllerMaker::direction(const tktkMath::Vector3& value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_direction = value;
		return *this;
	}

	ShadowMapCameraControllerMaker& ShadowMapCameraControllerMaker::initCameraWidth(float value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_initCameraWidth = value;
		return *this;
	}

	ShadowMapCameraControllerMaker& ShadowMapCameraControllerMaker::initCameraHeight(float value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_initCameraHeight = value;
		return *this;
	}

	ShadowMapCameraControllerMaker& ShadowMapCameraControllerMaker::initCameraNear(float value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_initCameraNear = value;
		return *this;
	}

	ShadowMapCameraControllerMaker& ShadowMapCameraControllerMaker::initCameraFar(float value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_initCameraFar = value;
		return *this;
	}
}