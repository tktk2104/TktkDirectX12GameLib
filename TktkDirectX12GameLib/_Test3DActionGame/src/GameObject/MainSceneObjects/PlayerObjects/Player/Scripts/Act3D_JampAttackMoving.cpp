#include "Act3D_JampAttackMoving.h"

void Act3D_JampAttackMoving::start()
{
	m_transform = getComponent<tktk::Transform3D>();

	if (m_transform.expired())
	{
		throw std::runtime_error("Act3D_JampAttackMoving not found Transform3D");
	}

	m_inertialMovement = getComponent<tktk::InertialMovement3D>();

	if (m_inertialMovement.expired())
	{
		throw std::runtime_error("Act3D_JampAttackMoving not found InertialMovement3D");
	}
}

void Act3D_JampAttackMoving::onEnable()
{
	m_verticalMoveSecTimer		= 0.0f;
	m_afterVerticalMove			= false;
	m_horizontalMoveSecTimer	= 0.0f;
}

void Act3D_JampAttackMoving::update()
{
	if (m_verticalMoveSecTimer < JmupVerticalMoveStartTimeSec)
	{
		m_verticalMoveSecTimer += tktk::DX12Game::deltaTime();
	}
	else if (!m_afterVerticalMove)
	{
		// ‚’¼•ûŒü‚É”ò‚Ñ’µ‚Ë‚é
		m_inertialMovement->addMomentarilyForce(m_transform->calculateWorldUp().normalized() * JumpVerticalPower);

		m_afterVerticalMove = true;
	}

	if (m_horizontalMoveSecTimer < JmupHorizontalMoveTimeSec)
	{
		m_horizontalMoveSecTimer += tktk::DX12Game::deltaTime();

		auto jumpSpeedPerSec = JumpHorizontalSpeedPerSec;

		if (!tktk::DX12Game::isPush(tktk::KeybordKeyType::key_W)) jumpSpeedPerSec *= 0.5f;

		m_transform->addLocalPosition(m_transform->calculateWorldForwardLH().normalized() * jumpSpeedPerSec * tktk::DX12Game::deltaTime());
		return;
	}
}