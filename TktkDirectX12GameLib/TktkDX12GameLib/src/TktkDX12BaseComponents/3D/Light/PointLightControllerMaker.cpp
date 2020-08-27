#include "TktkDX12BaseComponents/3D/Light/PointLightControllerMaker.h"

namespace tktk
{
	PointLightControllerMaker PointLightControllerMaker::m_self;

	PointLightControllerMaker& PointLightControllerMaker::makeStart(GameObjectPtr user)
	{
		// �ϐ�������������
		m_self = PointLightControllerMaker();

		// �����̃��[�U�[��ݒ�
		m_self.m_user = user;

		// ���g�̎Q�Ƃ�Ԃ�
		return m_self;
	}

	ComponentPtr<PointLightController> PointLightControllerMaker::create()
	{
		return m_user->createComponent<PointLightController>(
			m_initLightHandle,
			m_initAmbient,
			m_initDiffuse,
			m_initSpeqular
			);
	}

	PointLightControllerMaker& PointLightControllerMaker::initLightHandle(unsigned int value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_initLightHandle = value;
		return *this;
	}

	PointLightControllerMaker& PointLightControllerMaker::initAmbient(const tktkMath::Color& value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_initAmbient = value;
		return *this;
	}

	PointLightControllerMaker& PointLightControllerMaker::initDiffuse(const tktkMath::Color& value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_initDiffuse = value;
		return *this;
	}

	PointLightControllerMaker& PointLightControllerMaker::initSpeqular(const tktkMath::Color& value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_initSpeqular = value;
		return *this;
	}

	PointLightControllerMaker& PointLightControllerMaker::initLightIdImpl(int value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_initLightHandle = DX12GameManager::getLightHandle(value);
		return *this;
	}
}