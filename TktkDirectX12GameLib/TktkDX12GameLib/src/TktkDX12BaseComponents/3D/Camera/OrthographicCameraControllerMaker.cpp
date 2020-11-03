#include "TktkDX12BaseComponents/3D/Camera/OrthographicCameraControllerMaker.h"

namespace tktk
{
	OrthographicCameraControllerMaker OrthographicCameraControllerMaker::m_self;

	OrthographicCameraControllerMaker& OrthographicCameraControllerMaker::makeStart(GameObjectPtr user)
	{
		// �ϐ�������������
		m_self = OrthographicCameraControllerMaker();

		// �����̃��[�U�[��ݒ�
		m_self.m_user = user;

		// �g�p����J�����n���h���̃f�t�H���g�l�̓f�t�H���g�ʏ�J����
		m_self.m_initCameraHandle = DX12GameManager::getSystemHandle(SystemCameraType::DefaultCamera);

		// ���g�̎Q�Ƃ�Ԃ�
		return m_self;
	}

	OrthographicCameraControllerMaker& OrthographicCameraControllerMaker::makeStart(const StateTypeHierarchy& targetState, GameObjectPtr user)
	{
		// �ϐ�������������
		m_self = OrthographicCameraControllerMaker();

		// �����̃��[�U�[��ݒ�
		m_self.m_user = user;

		// �����̒ǉ��K�w��ݒ�
		m_self.m_targetState = targetState;

		// �g�p����J�����n���h���̃f�t�H���g�l�̓f�t�H���g�ʏ�J����
		m_self.m_initCameraHandle = DX12GameManager::getSystemHandle(SystemCameraType::DefaultCamera);

		// ���g�̎Q�Ƃ�Ԃ�
		return m_self;
	}

	ComponentPtr<OrthographicCameraController> OrthographicCameraControllerMaker::create()
	{
		// ���g��ǉ�����K�w��񂪋󂾂����畁�ʂɍ쐬����
		if (m_targetState.hierarchy.empty())
		{
			return m_user->createComponent<OrthographicCameraController>(
				m_initCameraHandle,
				m_initCameraWidth,
				m_initCameraHeight,
				m_initCameraNear,
				m_initCameraFar
				);
		}
		
		// �R���|�[�l���g���쐬����
		auto createComponent = m_user->createComponent<OrthographicCameraController>(
			m_initCameraHandle,
			m_initCameraWidth,
			m_initCameraHeight,
			m_initCameraNear,
			m_initCameraFar
			);

		// �쐬�����R���|�[�l���g�����̃X�e�[�g�ɒǉ�����
		m_user->setComponentToStateMachine(m_targetState, createComponent);

		// �쐬�����R���|�[�l���g�̃|�C���^��Ԃ�
		return createComponent;
	}

	OrthographicCameraControllerMaker& OrthographicCameraControllerMaker::initCameraHandle(unsigned int value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_initCameraHandle = value;
		return *this;
	}

	OrthographicCameraControllerMaker& OrthographicCameraControllerMaker::initCameraWidth(float value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_initCameraWidth = value;
		return *this;
	}

	OrthographicCameraControllerMaker& OrthographicCameraControllerMaker::initCameraHeight(float value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_initCameraHeight = value;
		return *this;
	}

	OrthographicCameraControllerMaker& OrthographicCameraControllerMaker::initCameraNear(float value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_initCameraNear = value;
		return *this;
	}

	OrthographicCameraControllerMaker& OrthographicCameraControllerMaker::initCameraFar(float value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_initCameraFar = value;
		return *this;
	}

	OrthographicCameraControllerMaker& OrthographicCameraControllerMaker::initCameraIdImpl(int value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_initCameraHandle = DX12GameManager::getCameraHandle(value);
		return *this;
	}
}