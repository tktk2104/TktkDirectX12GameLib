#include "TktkDX12BaseComponents/3D/Camera/BasicCameraControllerMaker.h"

#include "TktkDX12Game/_MainManager/DX12GameManager.h"
#include "TktkDX12Game/DXGameResource/GameObjectResouse/GameObject/GameObject.h"

namespace tktk
{
	BasicCameraControllerMaker BasicCameraControllerMaker::m_self;

	BasicCameraControllerMaker& BasicCameraControllerMaker::makeStart(GameObjectPtr user)
	{
		// �ϐ�������������
		m_self = BasicCameraControllerMaker();

		// �����̃��[�U�[��ݒ�
		m_self.m_user = user;

		// �g�p����J�����n���h���̃f�t�H���g�l�̓f�t�H���g�ʏ�J����
		m_self.m_initCameraHandle = DX12GameManager::getSystemHandle(SystemCameraType::DefaultCamera);

		// �J�����A�X�y�N�g��̃f�t�H���g�l�̓Q�[���X�N���[���̔䗦
		m_self.m_initCameraAspect = DX12GameManager::getDrawGameAreaSize().x / DX12GameManager::getDrawGameAreaSize().y;

		// ���g�̎Q�Ƃ�Ԃ�
		return m_self;
	}

	ComponentPtr<BasicCameraController> BasicCameraControllerMaker::create()
	{
		// �R���|�[�l���g���쐬����
		return m_user->createComponent<BasicCameraController>(
			m_initCameraHandle,
			m_initCameraFov,
			m_initCameraAspect,
			m_initCameraNear,
			m_initCameraFar
			);
	}

	BasicCameraControllerMaker& BasicCameraControllerMaker::initCameraHandle(size_t value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_initCameraHandle = value;
		return *this;
	}

	BasicCameraControllerMaker& BasicCameraControllerMaker::initCameraId(ResourceIdCarrier value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_initCameraHandle = DX12GameManager::getCameraHandle(value);
		return *this;
	}

	BasicCameraControllerMaker& BasicCameraControllerMaker::initCameraFov(float value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_initCameraFov = value;
		return *this;
	}

	BasicCameraControllerMaker& BasicCameraControllerMaker::initCameraAspect(float value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_initCameraAspect = value;
		return *this;
	}

	BasicCameraControllerMaker& BasicCameraControllerMaker::initCameraNear(float value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_initCameraNear = value;
		return *this;
	}

	BasicCameraControllerMaker& BasicCameraControllerMaker::initCameraFar(float value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_initCameraFar = value;
		return *this;
	}
}