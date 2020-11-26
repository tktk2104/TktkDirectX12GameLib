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
	if (m_playerParam.expired())
	{
		auto playerObject = tktk::DX12Game::findGameObjectWithTag(GameObjectTag::Player);

		if (playerObject.expired()) return;

		m_playerParam = playerObject->getComponent<Act3D_PlayerParam>();

		if (m_playerParam.expired()) return;
	}

	auto curScale = m_transform->getLocalScaleRate();

	m_transform->setLocalScaleRate({ static_cast<float>(m_playerParam->getCurHp()) / m_playerParam->getMaxHp(), curScale.y});
}
