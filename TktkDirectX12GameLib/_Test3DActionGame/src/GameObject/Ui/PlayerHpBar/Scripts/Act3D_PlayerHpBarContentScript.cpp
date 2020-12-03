#include "Act3D_PlayerHpBarContentScript.h"

#include "../../../../Enums/Enums.h"

void Act3D_PlayerHpBarContentScript::start()
{
	m_transform = getComponent<tktk::Transform2D>();

	if (m_transform.expired())
	{
		throw std::runtime_error("Act3D_PlayerHpBarContentScript not found Transform2D");
	}
}

void Act3D_PlayerHpBarContentScript::update()
{
	// �v���C���[�̔\�͒l���擾�ł��Ă��Ȃ����
	if (m_playerParam.expired())
	{
		// �v���C���[�I�u�W�F�N�g���擾����
		auto playerObject = tktk::DX12Game::findGameObjectWithTag(GameObjectTag::Player);

		// �v���C���[�I�u�W�F�N�g���擾�ł��Ȃ���Ώ������I����
		if (playerObject.expired()) return;

		// �v���C���[�̔\�͒l�̃R���|�[�l���g���擾����
		m_playerParam = playerObject->getComponent<Act3D_PlayerParam>();

		// �v���C���[�̔\�͒l�̃R���|�[�l���g���擾�ł��Ȃ���Ώ������I����
		if (m_playerParam.expired()) return;
	}

	// ���݂�Hp�̊������Q�Ƃ��Ď��g�̃X�P�[����ӂ�������
	m_transform->setLocalScaleRate({ static_cast<float>(m_playerParam->getCurHp()) / m_playerParam->getMaxHp(), m_transform->getLocalScaleRate().y});
}
