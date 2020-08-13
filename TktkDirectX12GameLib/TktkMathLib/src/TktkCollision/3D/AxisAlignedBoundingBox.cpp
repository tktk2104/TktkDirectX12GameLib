#include "TktkCollision/3D/AxisAlignedBoundingBox.h"

#include "TktkCollision/3D/Body3dBase/CollisionSupport3D.h"

AxisAlignedBoundingBox::AxisAlignedBoundingBox(
	const tktkMath::Vector3 & boxSize,
	const tktkMath::Vector3& localPosition
) 
	: Body3dBase(
		ShapeType3D::AABB,
		tktkMath::Matrix4::createTranslation(localPosition)
	)
	, m_boxSize(boxSize)
{
}

bool AxisAlignedBoundingBox::isCollide(const Body3dBase & other, HitInfo3D * hitinfo) const
{
	switch (other.getShapeType())
	{
	case ShapeType3D::Sphere:

		return CollisionSupport3D::collideAabbToSphere(*this, other, hitinfo);

	case ShapeType3D::AABB:

		return CollisionSupport3D::collideAabbToAabb(*this, other, hitinfo);
	}
	return false;
}

tktkMath::Vector3 AxisAlignedBoundingBox::calculateCornerPoint(CornerType cornerIndex) const
{
	tktkMath::Vector3 worldBoxSize = calculateBoxSize();

	tktkMath::Vector3 cornerLocalPosition;

	switch (cornerIndex)
	{
	case CornerType::LeftTopBack:		cornerLocalPosition = tktkMath::Vector3(-worldBoxSize.x / 2,  worldBoxSize.y / 2,  worldBoxSize.z / 2); break;
	case CornerType::RightTopBack:		cornerLocalPosition = tktkMath::Vector3( worldBoxSize.x / 2,  worldBoxSize.y / 2,  worldBoxSize.z / 2); break;
	case CornerType::LeftTopFront:		cornerLocalPosition = tktkMath::Vector3(-worldBoxSize.x / 2,  worldBoxSize.y / 2, -worldBoxSize.z / 2); break;
	case CornerType::RightTopFront:		cornerLocalPosition = tktkMath::Vector3( worldBoxSize.x / 2,  worldBoxSize.y / 2, -worldBoxSize.z / 2); break;
	case CornerType::LeftBottomBack:	cornerLocalPosition = tktkMath::Vector3(-worldBoxSize.x / 2, -worldBoxSize.y / 2,  worldBoxSize.z / 2); break;
	case CornerType::RightBottomBack:	cornerLocalPosition = tktkMath::Vector3( worldBoxSize.x / 2, -worldBoxSize.y / 2,  worldBoxSize.z / 2); break;
	case CornerType::LeftBottomFront:	cornerLocalPosition = tktkMath::Vector3(-worldBoxSize.x / 2, -worldBoxSize.y / 2, -worldBoxSize.z / 2); break;
	case CornerType::RightBottomFront:	cornerLocalPosition = tktkMath::Vector3( worldBoxSize.x / 2, -worldBoxSize.y / 2, -worldBoxSize.z / 2); break;
	}

	return calculatePose().calculateTranslation() + cornerLocalPosition;
}

tktkMath::Vector3 AxisAlignedBoundingBox::calculateBoxSize() const
{
	auto selfPose = calculatePose();

	// スケールのみを使用したワールド行列を作成する
	auto ignoreRotateWorldMatrix = tktkMath::Matrix4::createScale(selfPose.calculateScale()) * tktkMath::Matrix4::createTranslation(selfPose.calculateTranslation());

	return (tktkMath::Matrix4::createScale(m_boxSize) * ignoreRotateWorldMatrix).calculateScale();
}

tktkMath::Vector3 AxisAlignedBoundingBox::calculateLocalBoxSize() const
{
	auto selfPose = getLocalMatrix();

	// スケールのみを使用したワールド行列を作成する
	auto ignoreRotateWorldMatrix = tktkMath::Matrix4::createScale(selfPose.calculateScale()) * tktkMath::Matrix4::createTranslation(selfPose.calculateTranslation());

	return (tktkMath::Matrix4::createScale(m_boxSize) * ignoreRotateWorldMatrix).calculateScale();
}
