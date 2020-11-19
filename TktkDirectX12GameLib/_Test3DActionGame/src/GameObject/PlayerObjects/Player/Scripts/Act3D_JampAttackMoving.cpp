#include "Act3D_JampAttackMoving.h"

Act3D_JampAttackMoving::Act3D_JampAttackMoving(float jumpSpeedPerSec, float moveTimeSec)
	: m_jumpSpeedPerSec(jumpSpeedPerSec)
	, m_moveTimeSec(moveTimeSec)
{
}

void Act3D_JampAttackMoving::start()
{
	m_transform = getComponent<tktk::Transform3D>();

	if (m_transform.expired())
	{
		throw std::runtime_error("Act3D_JampAttackMoving not found Transform3D");
	}
}

void Act3D_JampAttackMoving::onEnable()
{
	m_moveSecTimer = 0.0f;
}

void Act3D_JampAttackMoving::update()
{
	if (m_moveSecTimer < m_moveTimeSec)
	{
		m_moveSecTimer += tktk::DX12Game::deltaTime();

		auto jumpSpeedPerSec = m_jumpSpeedPerSec;

		if (!tktk::DX12Game::isPush(tktk::KeybordKeyType::key_W)) jumpSpeedPerSec *= 0.5f;

		m_transform->addLocalPosition(m_transform->calculateWorldForwardLH().normalized() * jumpSpeedPerSec * tktk::DX12Game::deltaTime());
		return;
	}
}