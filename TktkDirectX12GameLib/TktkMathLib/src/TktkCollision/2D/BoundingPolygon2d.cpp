#include "TktkCollision/2D/BoundingPolygon2d.h"

#include "TktkCollision/2D/Body2dBase/CollisionSupport2D.h"

BoundingPolygon2d::BoundingPolygon2d(
	const std::vector<tktkMath::Vector2>& vertexs,
	const tktkMath::Vector2 & localPosition
)
	: Body2dBase(
		ShapeType2D::Polygon,
		tktkMath::Matrix3::createTranslation(localPosition)
	)
	, m_vertexs(vertexs)
{
}

bool BoundingPolygon2d::isCollide(const Body2dBase & other, HitInfo2D * hitinfo) const
{
	switch (other.getShapeType())
	{
	case ShapeType2D::Circle:

		return CollisionSupport2D::collidePolygonToCircle(*this, other, hitinfo);

	case ShapeType2D::Rect:

		return CollisionSupport2D::collidePolygonToRect(*this, other, hitinfo);

	case ShapeType2D::Polygon:

		return CollisionSupport2D::collidePolygonToPolygon(*this, other, hitinfo);
	}
	return false;
}

std::vector<tktkMath::Vector2> BoundingPolygon2d::calculateVertexs() const
{
	std::vector<tktkMath::Vector2> transformVertexs = m_vertexs;

	tktkMath::Matrix3 pose = calculatePose();

	for (auto & transformVertex : transformVertexs)
	{
		transformVertex *= pose;
	}
	return transformVertexs;
}

std::vector<tktkMath::Vector2> BoundingPolygon2d::calculateLocalVertexs() const
{
	std::vector<tktkMath::Vector2> transformVertexs = m_vertexs;

	tktkMath::Matrix3 pose = getLocalMatrix();

	for (auto & transformVertex : transformVertexs)
	{
		transformVertex *= pose;
	}
	return transformVertexs;
}
