#include "TktkDX12BaseComponents/2D/CircleCollider/CircleCollider.h"

#include <stdexcept>
#include "TktkDX12BaseComponents/2D/RectCollider/RectCollider.h"
#include "TktkDX12BaseComponents/2D/Polygon2dCollider/Polygon2dCollider.h"

namespace tktk
{
	CircleCollider::CircleCollider(
		int collisionGroupType,
		float radius,
		const tktkMath::Vector2 & localPosition
	)
		: ComponentBase(0.0f, collisionGroupType)
		, m_boundingCircle(radius, localPosition)
	{
	}

	void CircleCollider::start()
	{
		m_transform2D = getComponent<Transform2D>();

		if (m_transform2D.expired())
		{
			throw std::runtime_error("CircleCollider not found Transform2D");
		}
	}

	void CircleCollider::update()
	{
		m_boundingCircle.transform(m_transform2D->calculateWorldMatrix());
	}

	bool CircleCollider::isCollide(const ComponentBasePtr& other)
	{
		if (other.canCast<RectCollider>())
		{
			auto otherCollider = other.castPtr<RectCollider>();

			return m_boundingCircle.isCollide(otherCollider->getBodyBase(), &m_hitInfo);
		}

		if (other.canCast<CircleCollider>())
		{
			auto otherCollider = other.castPtr<CircleCollider>();

			return m_boundingCircle.isCollide(otherCollider->getBodyBase(), &m_hitInfo);
		}

		if (other.canCast<Polygon2dCollider>())
		{
			auto otherCollider = other.castPtr<Polygon2dCollider>();

			return m_boundingCircle.isCollide(otherCollider->getBodyBase(), &m_hitInfo);
		}
		return false;
	}

	const tktkCollision::Body2dBase & CircleCollider::getBodyBase() const
	{
		return m_boundingCircle;
	}

	const tktkCollision::HitInfo2D & CircleCollider::getHitInfo2D() const
	{
		return m_hitInfo;
	}
}