#include "TktkCollision/2D/BoundingCircle.h"

namespace tktkCollision
{
	BoundingCircle::BoundingCircle(float radius, const tktkMath::Vector2& centerPosition)
		: m_radius(radius)
		, m_centerPosition(centerPosition)
	{
	}

	float BoundingCircle::getRadius() const
	{
		return m_radius;
	}

	const tktkMath::Vector2& BoundingCircle::getCenterPosition() const
	{
		return m_centerPosition;
	}
}