#include "TktkDX12BaseComponents/3D/SphereCollider/SphereCollider.h"

#include <stdexcept>
#include "TktkDX12BaseComponents/3D/BoxCollider/BoxCollider.h"

namespace tktk
{
	SphereCollider::SphereCollider(
		int collisionGroupType,
		float radius,
		const tktkMath::Vector3 & localPosition
	)
		: ComponentBase(0.0f, collisionGroupType)
		, m_boundingSphere(radius, localPosition)
	{
	}

	void SphereCollider::start()
	{
		m_transform3D = getComponent<Transform3D>();

		if (m_transform3D.expired())
		{
			throw std::runtime_error("RectCollider not found Transform3D");
		}
	}

	void SphereCollider::update()
	{
		m_boundingSphere.transform(m_transform3D->calculateWorldMatrix());
	}

	bool SphereCollider::isCollide(const ComponentBasePtr& other)
	{
		if (other.canCast<BoxCollider>())
		{
			auto otherCollider = other.castPtr<BoxCollider>();

			return m_boundingSphere.isCollide(otherCollider->getBodyBase(), &m_hitInfo);
		}

		if (other.canCast<SphereCollider>())
		{
			auto otherCollider = other.castPtr<SphereCollider>();

			return m_boundingSphere.isCollide(otherCollider->getBodyBase(), &m_hitInfo);
		}

		return false;
	}

	const tktkCollision::Body3dBase & SphereCollider::getBodyBase() const
	{
		return m_boundingSphere;
	}

	const tktkCollision::HitInfo3D & SphereCollider::getHitInfo3D() const
	{
		return m_hitInfo;
	}
}