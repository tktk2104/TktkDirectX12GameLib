#include "TktkCollision/3D/BoundingSphere.h"

#include "TktkCollision/3D/CollisionSupport3D.h"

namespace tktkCollision
{
	BoundingSphere::BoundingSphere(float radius, const tktkMath::Vector3& centerPosition)
		: m_radius(radius)
		, m_centerPosition(centerPosition)
	{
	}

	float BoundingSphere::getRadius() const
	{
		return m_radius;
	}

	const tktkMath::Vector3& BoundingSphere::getCenterPosition() const
	{
		return m_centerPosition;
	}
}