#include "Sht2D_MoveForward.h"

Sht2D_MoveForward::Sht2D_MoveForward(float moveSpeedPerSec, float accelerationPerSec)
	: m_moveSpeedPerSec(moveSpeedPerSec)
	, m_accelerationPerSec(accelerationPerSec)
{
}

void Sht2D_MoveForward::start()
{
	m_transform = getComponent<tktk::Transform2D>();

	if (m_transform.expired())
	{
		throw std::runtime_error("Sht2D_MoveForward not found Transform2D");
	}

	m_inertialMovement = getComponent<tktk::InertialMovement2D>();

	if (m_inertialMovement.expired())
	{
		throw std::runtime_error("Sht2D_MoveForward not found InertialMovement2D");
	}
}

void Sht2D_MoveForward::update()
{
	// オブジェクトが向いている方向に継続的な加速を行う
	m_inertialMovement->addContinuousForce(m_transform->calculateLocalUp() * m_moveSpeedPerSec, m_accelerationPerSec);
}

float Sht2D_MoveForward::getMoveSpeedPerSec() const
{
	return m_moveSpeedPerSec;
}

void Sht2D_MoveForward::setMoveSpeedPerSec(float moveSpeed)
{
	m_moveSpeedPerSec = moveSpeed;
}
