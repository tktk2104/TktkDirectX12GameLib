#include "Act3D_EnemyJampAttackMoving.h"

Act3D_EnemyJampAttackMoving::Act3D_EnemyJampAttackMoving(float jumpSpeedPerSec, float moveTimeSec)
	: m_jumpSpeedPerSec(jumpSpeedPerSec)
	, m_moveTimeSec(moveTimeSec)
{
}

void Act3D_EnemyJampAttackMoving::start()
{
	m_transform = getComponent<tktk::Transform3D>();

	if (m_transform.expired())
	{
		throw std::runtime_error("Act3D_JampAttackMoving not found Transform3D");
	}
}

void Act3D_EnemyJampAttackMoving::onEnable()
{
	m_moveSecTimer = 0.0f;
}

void Act3D_EnemyJampAttackMoving::update()
{
	if (m_moveSecTimer < m_moveTimeSec)
	{
		m_moveSecTimer += tktk::DX12Game::deltaTime();

		m_transform->addLocalPosition(m_transform->calculateWorldForwardLH().normalized() * m_jumpSpeedPerSec * tktk::DX12Game::deltaTime());
		return;
	}
}
