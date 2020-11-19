#include "Act3D_GravityMove.h"

Act3D_GravityMove::Act3D_GravityMove(float gravityPower)
	: m_gravityPower(gravityPower)
{
}

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
	m_inertialMovement->addContinuousForce(tktkMath::Vector3_v::down * m_gravityPower, 6.0f);
}
