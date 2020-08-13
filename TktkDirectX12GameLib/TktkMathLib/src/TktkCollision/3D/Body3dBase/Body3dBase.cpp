#include "TktkCollision/3D/Body3dBase/Body3dBase.h"

namespace tktkCollision
{
	Body3dBase::Body3dBase(
		ShapeType3D shapeType,
		const tktkMath::Matrix4& localMatrix
	)
		: m_shapeType(shapeType)
		, m_worldMatrix(tktkMath::Matrix4_v::identity)
		, m_localMatrix(localMatrix)
	{
	}

	void Body3dBase::transform(const tktkMath::Matrix4& world)
	{
		m_worldMatrix = world;
	}

	tktkMath::Matrix4 Body3dBase::calculatePose() const
	{
		return m_localMatrix * m_worldMatrix;
	}

	const tktkMath::Matrix4& Body3dBase::getWorldMatrix() const
	{
		return m_worldMatrix;
	}

	const tktkMath::Matrix4& Body3dBase::getLocalMatrix() const
	{
		return m_localMatrix;
	}

	void Body3dBase::setLocalMatrix(const tktkMath::Matrix4& localMatrix)
	{
		m_localMatrix = localMatrix;
	}

	ShapeType3D Body3dBase::getShapeType() const
	{
		return m_shapeType;
	}
}

