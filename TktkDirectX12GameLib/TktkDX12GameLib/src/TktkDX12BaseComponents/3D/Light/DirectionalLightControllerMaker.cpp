#include "TktkDX12BaseComponents/3D/Light/DirectionalLightControllerMaker.h"

namespace tktk
{
	DirectionalLightControllerMaker DirectionalLightControllerMaker::m_self;

	DirectionalLightControllerMaker& DirectionalLightControllerMaker::makeStart(GameObjectPtr user)
	{
		// �ϐ�������������
		m_self = DirectionalLightControllerMaker();

		// �����̃��[�U�[��ݒ�
		m_self.m_user = user;

		// �g�p���郉�C�g�n���h���̃f�t�H���g�l�̓f�t�H���g���C�g
		m_self.m_initLightHandle = DX12GameManager::getSystemHandle(SystemLightType::DefaultLight);

		// ���g�̎Q�Ƃ�Ԃ�
		return m_self;
	}

	DirectionalLightControllerMaker& DirectionalLightControllerMaker::makeStart(const StateTypeHierarchy& targetState, GameObjectPtr user)
	{
		// �ϐ�������������
		m_self = DirectionalLightControllerMaker();

		// �����̃��[�U�[��ݒ�
		m_self.m_user = user;

		// �����̒ǉ��K�w��ݒ�
		m_self.m_targetState = targetState;

		// �g�p���郉�C�g�n���h���̃f�t�H���g�l�̓f�t�H���g���C�g
		m_self.m_initLightHandle = DX12GameManager::getSystemHandle(SystemLightType::DefaultLight);

		// ���g�̎Q�Ƃ�Ԃ�
		return m_self;
	}

	ComponentPtr<DirectionalLightController> DirectionalLightControllerMaker::create()
	{
		// ���g��ǉ�����K�w��񂪋󂾂����畁�ʂɍ쐬����
		if (m_targetState.hierarchy.empty())
		{
			return  m_user->createComponent<DirectionalLightController>(
				m_initLightHandle,
				m_initAmbient,
				m_initDiffuse,
				m_initSpeqular
				);
		}

		// �R���|�[�l���g���쐬����
		auto createComponent = m_user->createComponent<DirectionalLightController>(
			m_initLightHandle,
			m_initAmbient,
			m_initDiffuse,
			m_initSpeqular
			);

		// �쐬�����R���|�[�l���g�����̃X�e�[�g�ɒǉ�����
		m_user->setComponentToStateMachine(m_targetState, createComponent);

		// �쐬�����R���|�[�l���g�̃|�C���^��Ԃ�
		return createComponent;
	}

	DirectionalLightControllerMaker& DirectionalLightControllerMaker::initLightHandle(unsigned int value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_initLightHandle = value;
		return *this;
	}

	DirectionalLightControllerMaker& DirectionalLightControllerMaker::initAmbient(const tktkMath::Color& value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_initAmbient = value;
		return *this;
	}

	DirectionalLightControllerMaker& DirectionalLightControllerMaker::initDiffuse(const tktkMath::Color& value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_initDiffuse = value;
		return *this;
	}

	DirectionalLightControllerMaker& DirectionalLightControllerMaker::initSpeqular(const tktkMath::Color& value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_initSpeqular = value;
		return *this;
	}

	DirectionalLightControllerMaker& DirectionalLightControllerMaker::initLightIdImpl(int value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_initLightHandle = DX12GameManager::getLightHandle(value);
		return *this;
	}
}