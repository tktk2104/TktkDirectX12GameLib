#include "TktkDX12BaseComponents/2D/InertialRotatement2D/InertialRotatement2D.h"

#include <stdexcept>
#include <TktkMath/MathHelper.h>
#include <TktkDX12BaseComponents/2D/Transform2D/Transform2D.h>
#include <TktkDX12Game/_MainManager/DX12GameManager.h>

namespace tktk
{
	InertialRotatement2D::InertialRotatement2D(
		float decelerationPerSec,
		float initVelocity
	)
		: m_velocity(initVelocity)
		, m_decelerationPerSec(decelerationPerSec)
	{
	}

	void InertialRotatement2D::start()
	{
		m_transform2D = getComponent<Transform2D>();

		if (m_transform2D.expired())
		{
			throw std::runtime_error("InertialRotatement2D not found Transform2D");
		}
	}

	void InertialRotatement2D::update()
	{
		// 回転速度分自身を回転させる
		m_transform2D->addLocalRotationDeg(m_velocity * DX12GameManager::deltaTime());

		// 速度を減速する
		float speed = std::abs(m_velocity) - (m_decelerationPerSec * DX12GameManager::deltaTime());

		// 速度が負の数になっていたら速度をゼロにする
		if (speed < 0.0f) speed = 0.0f;

		// 回転速度の値を更新する
		m_velocity = tktkMath::MathHelper::sign(m_velocity) * speed;
	}

	void InertialRotatement2D::addMomentarilyForce(float force)
	{
		if (std::abs(force) < tktkMath::MathHelper::kEpsilon) return;

		m_velocity += force;
	}

	void InertialRotatement2D::addContinuousForce(float force, float accelerationPerSec)
	{
		if (std::abs(force) < tktkMath::MathHelper::kEpsilon) return;

		float velocityDist = force - m_velocity;

		float acceleration = accelerationPerSec * DX12GameManager::deltaTime();

		if (std::abs(velocityDist) > acceleration)
		{
			m_velocity += tktkMath::MathHelper::sign(velocityDist) * acceleration;
			return;
		}
		m_velocity += velocityDist;
	}

	float InertialRotatement2D::getVelocity() const
	{
		return m_velocity;
	}

	void InertialRotatement2D::setVelocity(float velocity)
	{
		m_velocity = velocity;
	}
}
