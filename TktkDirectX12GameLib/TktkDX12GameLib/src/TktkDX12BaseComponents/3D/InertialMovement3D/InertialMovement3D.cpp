#include "TktkDX12BaseComponents/3D/InertialMovement3D/InertialMovement3D.h"

#include <stdexcept>
#include <TktkMath/MathHelper.h>
#include "TktkDX12BaseComponents/3D/Transform3D/Transform3D.h"
#include "TktkDX12Game/_MainManager/DX12GameManager.h"

namespace tktk
{
	InertialMovement3D::InertialMovement3D(
		float decelerationPerSec,
		const tktkMath::Vector3 & initVelocity
	)
		: m_velocity(initVelocity)
		, m_decelerationPerSec(decelerationPerSec)
	{
	}

	void InertialMovement3D::start()
	{
		m_transform3D = getComponent<Transform3D>();

		if (m_transform3D.expired())
		{
			throw std::runtime_error("InertialMovement3D not found Transform3D");
		}
	}

	void InertialMovement3D::update()
	{
		// 移動速度分自身の座標を移動する
		m_transform3D->addLocalPosition(m_velocity * DX12GameManager::deltaTime());

		// 速度を減速する
		float speed = (m_velocity.length() - (m_decelerationPerSec * DX12GameManager::deltaTime()));

		// 速度が負の数になっていたら速度をゼロにする
		if (speed < 0.0f) speed = 0.0f;

		// 移動速度の値を更新する
		m_velocity = tktkMath::Vector3::normalize(m_velocity) * speed;
	}

	void InertialMovement3D::addMomentarilyForce(const tktkMath::Vector3 & force)
	{
		if (force.length() < tktkMath::MathHelper::kEpsilon) return;

		m_velocity += force;
	}

	void InertialMovement3D::addContinuousForce(const tktkMath::Vector3 & force, float accelerationPerSec)
	{
		if (force.length() < tktkMath::MathHelper::kEpsilon) return;

		// 目標とする速度との差
		tktkMath::Vector3 velocityDist = force - m_velocity;

		float acceleration = accelerationPerSec * DX12GameManager::deltaTime();

		if (velocityDist.length() > acceleration)
		{
			m_velocity += velocityDist.normalized() * acceleration;
			return;
		}
		m_velocity += velocityDist;
	}

	tktkMath::Vector3 InertialMovement3D::getVelocity() const
	{
		return m_velocity;
	}

	void InertialMovement3D::setVelocity(const tktkMath::Vector3 & velocity)
	{
		m_velocity = velocity;
	}
}