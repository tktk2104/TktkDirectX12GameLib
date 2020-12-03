#include "TktkCollision/2D/BoundingPolygon2D.h"

namespace tktkCollision
{
	BoundingPolygon2D::BoundingPolygon2D(const std::vector<tktkMath::Vector2>& vertexs)
		: m_vertexs(vertexs)
	{
	}

	const std::vector<tktkMath::Vector2>& BoundingPolygon2D::getVertexs() const
	{
		return m_vertexs;
	}
}