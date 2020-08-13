#include "TktkDX12BaseComponents/2D/InertialMovement2D/InertialMovement2D.h"

#include <stdexcept>
#include <TktkMath/MathHelper.h>

namespace tktk
{
	InertialMovement2D::InertialMovement2D(
		float decelerationPerSec,
		const tktkMath::Vector2 & initVelocity
	)
		: m_velocity(initVelocity)
		, m_decelerationPerSec(decelerationPerSec)
	{
	}

	void InertialMovement2D::start()
	{
		m_transform2D = getComponent<Transform2D>();

		if (m_transform2D.expired())
		{
			throw std::runtime_error("InertialMovement2D not found Transform2D");
		}
	}

	void InertialMovement2D::update()
	{
		m_transform2D->addLocalPosition(m_velocity * DX12GameManager::deltaTime());

		if (!m_preFrameAddForce)
		{
			float speed = (m_velocity.length() - (m_decelerationPerSec * DX12GameManager::deltaTime()));

			if (speed < 0.0f) speed = 0.0f;

			m_velocity = tktkMath::Vector2::normalize(m_velocity) * speed;
		}
		m_preFrameAddForce = false;
	}

	void InertialMovement2D::addMomentarilyForce(const  tktkMath::Vector2 & force)
	{
		if (force.length() < tktkMath::MathHelper::kEpsilon) return;

		m_preFrameAddForce = true;

		m_velocity += force;
	}

	void InertialMovement2D::addContinuousForce(const  tktkMath::Vector2 & force, float accelerationPerSec)
	{
		if (force.length() < tktkMath::MathHelper::kEpsilon) return;

		m_preFrameAddForce = true;

		// –Ú•W‚Æ‚·‚é‘¬“x‚Æ‚Ì·
		tktkMath::Vector2 velocityDist = force - m_velocity;

		float acceleration = accelerationPerSec * DX12GameManager::deltaTime();

		if (velocityDist.length() > acceleration)
		{
			m_velocity += velocityDist.normalized() * acceleration;
			return;
		}
		m_velocity += velocityDist;
	}

	const  tktkMath::Vector2 & InertialMovement2D::getVelocity() const
	{
		return m_velocity;
	}

	void InertialMovement2D::setVelocity(const  tktkMath::Vector2 & velocity)
	{
		m_velocity = velocity;
	}
}