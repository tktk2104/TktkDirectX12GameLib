#include "TktkCollision/3D/BoundingSphere.h"

#include "TktkCollision/3D/Body3dBase/CollisionSupport3D.h"

BoundingSphere::BoundingSphere(
	float radius,
	const tktkMath::Vector3 & localPosition
)
	: Body3dBase(
		ShapeType3D::Sphere,
		tktkMath::Matrix4::createTranslation(localPosition)
	)
	, m_radius(radius)
{
}

bool BoundingSphere::isCollide(const Body3dBase & other, HitInfo3D * hitinfo) const
{
	switch (other.getShapeType())
	{
	case ShapeType3D::Sphere:

		return CollisionSupport3D::collideSphereToSphere(*this, other, hitinfo);

	case ShapeType3D::AABB:

		return CollisionSupport3D::collideSphereToAabb(*this, other, hitinfo);
	}
	return false;
}

float BoundingSphere::calculateRadius() const
{
	tktkMath::Matrix4 worldRadius = tktkMath::Matrix4::createScale(tktkMath::Vector3(m_radius, m_radius, m_radius)) * calculatePose();

	return worldRadius.calculateScale().x;
}

float BoundingSphere::calculateLocalRadius() const
{
	tktkMath::Matrix4 worldRadius = tktkMath::Matrix4::createScale(tktkMath::Vector3(m_radius, m_radius, m_radius)) * getLocalMatrix();

	return worldRadius.calculateScale().x;
}
