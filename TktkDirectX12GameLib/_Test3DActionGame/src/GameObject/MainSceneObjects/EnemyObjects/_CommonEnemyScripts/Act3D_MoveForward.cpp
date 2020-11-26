#include "Act3D_MoveForward.h"

Act3D_MoveForward::Act3D_MoveForward(float moveSpeedPerSec)
	: m_moveSpeedPerSec(moveSpeedPerSec)
{
}

void Act3D_MoveForward::start()
{
	m_selfTransform = getComponent<tktk::Transform3D>();

	if (m_selfTransform.expired())
	{
		throw std::runtime_error("Act3D_MoveForward not found Transform3D");
	}
}

void Act3D_MoveForward::update()
{
	m_selfTransform->addLocalPosition(m_selfTransform->calculateLocalForwardLH().normalized() * m_moveSpeedPerSec * tktk::DX12Game::deltaTime());
}
