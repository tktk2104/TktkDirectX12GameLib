#include "TktkCollision/2D/BoundingCircle.h"

namespace tktkCollision
{
	BoundingCircle::BoundingCircle(float radius, const tktkMath::Vector2& centerPosition)
		: m_baseRadius(radius)
		, m_baseCenterPosition(centerPosition)
		, m_transformedRadius(radius)
		, m_transformedCenterPosition(centerPosition)
	{
	}

	void BoundingCircle::transform(const tktkMath::Matrix3& worldMatrix)
	{
		m_transformedCenterPosition = m_baseCenterPosition * worldMatrix;
		m_transformedRadius			= m_baseRadius * worldMatrix.calculateScale().x;
	}

	float BoundingCircle::getRadius() const
	{
		return m_baseRadius;
	}

	const tktkMath::Vector2& BoundingCircle::getCenterPosition() const
	{
		return m_baseCenterPosition;
	}

	float BoundingCircle::getTransformedRadius() const
	{
		return m_transformedRadius;
	}

	const tktkMath::Vector2& BoundingCircle::getTransformedCenterPosition() const
	{
		return m_transformedCenterPosition;
	}
}