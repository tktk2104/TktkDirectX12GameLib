#include "TktkCollision/2D/BoundingPolygon2D.h"

namespace tktkCollision
{
	BoundingPolygon2D::BoundingPolygon2D(const std::vector<tktkMath::Vector2>& vertexs)
		: m_baseVertexs(vertexs)
		, m_transformedVertexs(vertexs)
	{
	}

	void BoundingPolygon2D::transform(const tktkMath::Matrix3& worldMatrix)
	{
		for (size_t i = 0U; i < m_baseVertexs.size(); i++)
		{
			m_transformedVertexs.at(i) = m_baseVertexs.at(i) * worldMatrix;
		}
	}

	const std::vector<tktkMath::Vector2>& BoundingPolygon2D::getVertexs() const
	{
		return m_baseVertexs;
	}

	const std::vector<tktkMath::Vector2>& BoundingPolygon2D::getTransformedVertexs() const
	{
		return m_transformedVertexs;
	}
}