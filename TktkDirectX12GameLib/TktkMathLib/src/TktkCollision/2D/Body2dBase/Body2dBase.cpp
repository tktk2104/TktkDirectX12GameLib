#include "TktkCollision/2D/Body2dBase/Body2dBase.h"

Body2dBase::Body2dBase(
	ShapeType2D shapeType,
	const tktkMath::Matrix3 & localMatrix
)
	: m_shapeType(shapeType)
	, m_worldMatrix(tktkMath::Matrix3_v::identity)
	, m_localMatrix(localMatrix)
{
}

Body2dBase::~Body2dBase()
{
}

void Body2dBase::transform(const tktkMath::Matrix3 & world)
{
	m_worldMatrix = world;
}

tktkMath::Matrix3 Body2dBase::calculatePose() const
{
	return m_localMatrix * m_worldMatrix;
}

const tktkMath::Matrix3 & Body2dBase::getWorldMatrix() const
{
	return m_worldMatrix;
}

const tktkMath::Matrix3 & Body2dBase::getLocalMatrix() const
{
	return m_localMatrix;
}

void Body2dBase::setLocalMatrix(const tktkMath::Matrix3 & localMatrix)
{
	m_localMatrix = localMatrix;
}

ShapeType2D Body2dBase::getShapeType() const
{
	return m_shapeType;
}
