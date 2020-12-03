#include "TktkCollision/3D/BoundingSphere.h"

#include "TktkCollision/3D/CollisionSupport3D.h"

namespace tktkCollision
{
	BoundingSphere::BoundingSphere(float radius, const tktkMath::Vector3& centerPosition)
		: m_baseRadius(radius)
		, m_baseCenterPosition(centerPosition)
		, m_transformedRadius(radius)
		, m_transformedCenterPosition(centerPosition)
	{
	}

	void BoundingSphere::transform(const tktkMath::Matrix4& worldMatrix)
	{
		m_transformedCenterPosition = m_baseCenterPosition * worldMatrix;
		m_transformedRadius			= m_baseRadius * worldMatrix.calculateScale().x;
	}

	float BoundingSphere::getBaseRadius() const
	{
		return m_baseRadius;
	}

	const tktkMath::Vector3& BoundingSphere::getBaseCenterPosition() const
	{
		return m_baseCenterPosition;
	}

	float BoundingSphere::getTransformedRadius() const
	{
		return m_transformedRadius;
	}

	const tktkMath::Vector3& BoundingSphere::getTransformedCenterPosition() const
	{
		return m_transformedCenterPosition;
	}
}