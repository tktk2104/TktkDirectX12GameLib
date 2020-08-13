#include "TktkDX12BaseComponents/3D/BoxCollider/BoxCollider.h"

#include <stdexcept>
#include "TktkDX12BaseComponents/3D/SphereCollider/SphereCollider.h"

namespace tktk
{
	BoxCollider::BoxCollider(
		int collisionGroupType,
		const tktkMath::Vector3 & boxSize,
		const tktkMath::Vector3 & localPosition
	)
		: ComponentBase(0.0f, collisionGroupType)
		, m_boundingBox(boxSize, localPosition)
	{
	}

	void BoxCollider::start()
	{
		m_transform3D = getComponent<Transform3D>();

		if (m_transform3D.expired())
		{
			throw std::runtime_error("RectCollider not found Transform3D");
		}
	}

	void BoxCollider::update()
	{
		m_boundingBox.transform(m_transform3D->calculateWorldMatrix());
	}

	bool BoxCollider::isCollide(const ComponentBasePtr& other)
	{
		if (other.canCast<BoxCollider>())
		{
			auto otherCollider = other.castPtr<BoxCollider>();

			return m_boundingBox.isCollide(otherCollider->getBodyBase(), &m_hitInfo);
		}

		if (other.canCast<SphereCollider>())
		{
			auto otherCollider = other.castPtr<SphereCollider>();

			return m_boundingBox.isCollide(otherCollider->getBodyBase(), &m_hitInfo);
		}

		return false;
	}

	const tktkCollision::Body3dBase & BoxCollider::getBodyBase() const
	{
		return m_boundingBox;
	}

	const tktkCollision::HitInfo3D & BoxCollider::getHitInfo3D() const
	{
		return m_hitInfo;
	}
}