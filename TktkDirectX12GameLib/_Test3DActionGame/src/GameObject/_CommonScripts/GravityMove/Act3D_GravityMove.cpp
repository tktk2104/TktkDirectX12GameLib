#include "Act3D_GravityMove.h"

void Act3D_GravityMove::start()
{
	m_inertialMovement = getComponent<tktk::InertialMovement3D>();

	if (m_inertialMovement.expired())
	{
		throw std::runtime_error("Act3D_GravityMove not found InertialMovement3D");
	}
}

void Act3D_GravityMove::update()
{
	// 重力分加速する
	m_inertialMovement->addContinuousForce(tktkMath::Vector3_v::down * GravityPower, GravityAccelerationPerSec);
}
