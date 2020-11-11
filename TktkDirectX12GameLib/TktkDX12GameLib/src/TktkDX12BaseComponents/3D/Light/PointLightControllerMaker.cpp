#include "TktkDX12BaseComponents/3D/Light/PointLightControllerMaker.h"

#include "TktkDX12Game/_MainManager/DX12GameManager.h"
#include "TktkDX12Game/DXGameResource/GameObjectResouse/GameObject/GameObject.h"

namespace tktk
{
	PointLightControllerMaker PointLightControllerMaker::m_self;

	PointLightControllerMaker& PointLightControllerMaker::makeStart(GameObjectPtr user)
	{
		// �ϐ�������������
		m_self = PointLightControllerMaker();

		// �����̃��[�U�[��ݒ�
		m_self.m_user = user;

		// �g�p���郉�C�g�n���h���̃f�t�H���g�l�̓f�t�H���g���C�g
		m_self.m_initLightHandle = DX12GameManager::getSystemHandle(SystemLightType::DefaultLight);

		// ���g�̎Q�Ƃ�Ԃ�
		return m_self;
	}

	ComponentPtr<PointLightController> PointLightControllerMaker::create()
	{
		// �R���|�[�l���g���쐬����
		return m_user->createComponent<PointLightController>(
			m_initLightHandle,
			m_initAmbient,
			m_initDiffuse,
			m_initSpeqular
			);
	}

	PointLightControllerMaker& PointLightControllerMaker::initLightHandle(size_t value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_initLightHandle = value;
		return *this;
	}

	PointLightControllerMaker& PointLightControllerMaker::initLightId(ResourceIdCarrier value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_initLightHandle = DX12GameManager::getLightHandle(value);
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
}