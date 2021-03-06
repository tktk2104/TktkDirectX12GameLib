#include "TktkDX12BaseComponents/2D/InertialMovement2D/InertialMovement2D.h"

#include <stdexcept>
#include <TktkMath/MathHelper.h>
#include "TktkDX12BaseComponents/2D/Transform2D/Transform2D.h"
#include "TktkDX12Game/_MainManager/DX12GameManager.h"

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
		// 移動速度分自身の座標を移動する
		m_transform2D->addLocalPosition(m_velocity * DX12GameManager::deltaTime());

		// 速度を減速する
		float speed = (m_velocity.length() - (m_decelerationPerSec * DX12GameManager::deltaTime()));

		// 速度が負の数になっていたら速度をゼロにする
		if (speed < 0.0f) speed = 0.0f;

		// 移動速度の値を更新する
		m_velocity = tktkMath::Vector2::normalize(m_velocity) * speed;
	}

	void InertialMovement2D::addMomentarilyForce(const  tktkMath::Vector2 & force)
	{
		if (force.length() < tktkMath::MathHelper::kEpsilon) return;

		m_velocity += force;
	}

	void InertialMovement2D::addContinuousForce(const  tktkMath::Vector2 & force, float accelerationPerSec)
	{
		if (force.length() < tktkMath::MathHelper::kEpsilon) return;

		// 目標とする速度との差
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