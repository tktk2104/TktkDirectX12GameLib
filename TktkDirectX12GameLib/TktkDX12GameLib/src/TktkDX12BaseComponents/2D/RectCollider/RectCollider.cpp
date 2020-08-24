#include "TktkDX12BaseComponents/2D/RectCollider/RectCollider.h"

#include <vector>
#include <stdexcept>
#include <iterator>
#include <algorithm>
#include "TktkDX12BaseComponents/2D/CircleCollider/CircleCollider.h"
#include "TktkDX12BaseComponents/2D/Polygon2dCollider/Polygon2dCollider.h"

namespace tktk
{
	RectCollider::RectCollider(
		int collisionGroupType,
		const tktkMath::Vector2& rectSize,
		const tktkMath::Vector2& localPosition
	)
		: ComponentBase(0.0f, collisionGroupType)
		, m_boundingPolygon2d({ {-rectSize.x / 2, -rectSize.y / 2}, {rectSize.x / 2, -rectSize.y / 2}, {rectSize.x / 2,  rectSize.y / 2}, {-rectSize.x / 2,  rectSize.y / 2} }, localPosition)
	{
	}

	void RectCollider::start()
	{
		m_transform2D = getComponent<Transform2D>();

		if (m_transform2D.expired())
		{
			throw std::runtime_error("RectCollider not found Transform2D");
		}
	}

	void RectCollider::update()
	{
		m_boundingPolygon2d.transform(m_transform2D->calculateWorldMatrix());
	}

	bool RectCollider::isCollide(const ComponentBasePtr& other)
	{
		if (other.canCast<RectCollider>())
		{
			auto otherCollider = other.castPtr<RectCollider>();

			return m_boundingPolygon2d.isCollide(otherCollider->getBodyBase(), &m_hitInfo);
		}

		if (other.canCast<CircleCollider>())
		{
			auto otherCollider = other.castPtr<CircleCollider>();

			return m_boundingPolygon2d.isCollide(otherCollider->getBodyBase(), &m_hitInfo);
		}

		if (other.canCast<Polygon2dCollider>())
		{
			auto otherCollider = other.castPtr<Polygon2dCollider>();

			return m_boundingPolygon2d.isCollide(otherCollider->getBodyBase(), &m_hitInfo);
		}
		return false;
	}

	const tktkCollision::Body2dBase & RectCollider::getBodyBase() const
	{
		return m_boundingPolygon2d;
	}
}