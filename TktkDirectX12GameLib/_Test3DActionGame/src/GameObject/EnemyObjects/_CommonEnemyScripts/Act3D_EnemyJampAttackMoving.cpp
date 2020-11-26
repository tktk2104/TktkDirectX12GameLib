#include "Act3D_EnemyJampAttackMoving.h"

Act3D_EnemyJampAttackMoving::Act3D_EnemyJampAttackMoving(float jumpVerticalPower, float jmupVerticalMoveStartTimeSec, float jumpHorizontalSpeedPerSec, float jmupHorizontalMoveTimeSec)
	: m_jumpVerticalPower(jumpVerticalPower)
	, m_jmupVerticalMoveStartTimeSec(jmupVerticalMoveStartTimeSec)
	, m_jumpHorizontalSpeedPerSec(jumpHorizontalSpeedPerSec)
	, m_jmupHorizontalMoveTimeSec(jmupHorizontalMoveTimeSec)
{
}

void Act3D_EnemyJampAttackMoving::start()
{
	m_transform = getComponent<tktk::Transform3D>();

	if (m_transform.expired())
	{
		throw std::runtime_error("Act3D_EnemyJampAttackMoving not found Transform3D");
	}
	m_inertialMovement = getComponent<tktk::InertialMovement3D>();

	if (m_inertialMovement.expired())
	{
		throw std::runtime_error("Act3D_EnemyJampAttackMoving not found InertialMovement3D");
	}

}

void Act3D_EnemyJampAttackMoving::onEnable()
{
	m_verticalMoveSecTimer		= 0.0f;
	m_afterVerticalMove			= false;
	m_horizontalMoveSecTimer	= 0.0f;
}

void Act3D_EnemyJampAttackMoving::update()
{
	if (m_verticalMoveSecTimer < m_jmupVerticalMoveStartTimeSec)
	{
		m_verticalMoveSecTimer += tktk::DX12Game::deltaTime();
	}
	else if (!m_afterVerticalMove)
	{
		// ‚’¼•ûŒü‚É”ò‚Ñ’µ‚Ë‚é
		m_inertialMovement->addMomentarilyForce(m_transform->calculateWorldUp().normalized() * m_jumpVerticalPower);

		m_afterVerticalMove = true;
	}

	if (m_horizontalMoveSecTimer < m_jmupHorizontalMoveTimeSec)
	{
		m_horizontalMoveSecTimer += tktk::DX12Game::deltaTime();

		m_transform->addLocalPosition(m_transform->calculateWorldForwardLH().normalized() * m_jumpHorizontalSpeedPerSec * tktk::DX12Game::deltaTime());
		return;
	}
}
