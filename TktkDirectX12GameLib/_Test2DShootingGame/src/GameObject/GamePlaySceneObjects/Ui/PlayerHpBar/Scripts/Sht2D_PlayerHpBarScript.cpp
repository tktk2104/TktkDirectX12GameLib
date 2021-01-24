#include "Sht2D_PlayerHpBarScript.h"

#include "../../../../../Enums/Enums.h"

void Sht2D_PlayerHpBarScript::start()
{
	m_transform = getComponent<tktk::Transform2D>();

	if (m_transform.expired())
	{
		throw std::runtime_error("Sht2D_PlayerHpBarScript not found Transform2D");
	}
}

void Sht2D_PlayerHpBarScript::update()
{
	// �v���C���[�̔\�͒l���擾�ł��Ă��Ȃ����
	if (m_healthPoint.expired())
	{
		// �v���C���[�I�u�W�F�N�g���擾����
		auto playerObject = tktk::DX12Game::findGameObjectWithTag(GameObjectTag::Player);

		// �v���C���[�I�u�W�F�N�g���擾�ł��Ȃ���Ώ������I����
		if (playerObject.expired()) return;

		// �v���C���[�̔\�͒l�̃R���|�[�l���g���擾����
		m_healthPoint = playerObject->getComponent<Sht2D_HealthPoint>();

		// �v���C���[�̔\�͒l�̃R���|�[�l���g���擾�ł��Ȃ���Ώ������I����
		if (m_healthPoint.expired()) return;
	}

	// ���݂�Hp�̊������Q�Ƃ��Ď��g�̃X�P�[����ӂ�������
	m_transform->setLocalScaleRate({ static_cast<float>(m_healthPoint->getCurHp()) / m_healthPoint->getMaxHp(), m_transform->getLocalScaleRate().y });
}
