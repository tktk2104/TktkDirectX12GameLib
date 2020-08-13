#include "TktkDX12BaseComponents/2D/Polygon2dCollider/Polygon2dCollider.h"

#include <vector>
#include <stdexcept>
#include <iterator>
#include <algorithm>
#include "TktkDX12BaseComponents/2D/RectCollider/RectCollider.h"
#include "TktkDX12BaseComponents/2D/CircleCollider/CircleCollider.h"

namespace tktk
{
	Polygon2dCollider::Polygon2dCollider(
		int collisionGroupType,
		const std::vector<tktkMath::Vector2>& vertexs,
		const tktkMath::Vector2 & localPosition
	)
		: ComponentBase(0.0f, collisionGroupType)
		, m_boundingPolygon2d(vertexs, localPosition)
	{
	}

	void Polygon2dCollider::start()
	{
		m_transform2D = getComponent<Transform2D>();

		if (m_transform2D.expired())
		{
			throw std::runtime_error("RectCollider not found Transform2D");
		}
	}

	void Polygon2dCollider::update()
	{
		m_boundingPolygon2d.transform(m_transform2D->calculateWorldMatrix());
	}

	bool Polygon2dCollider::isCollide(const ComponentBasePtr& other)
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

	const tktkCollision::Body2dBase & Polygon2dCollider::getBodyBase() const
	{
		return m_boundingPolygon2d;
	}

	const tktkCollision::HitInfo2D & Polygon2dCollider::getHitInfo2D() const
	{
		return m_hitInfo;
	}
}