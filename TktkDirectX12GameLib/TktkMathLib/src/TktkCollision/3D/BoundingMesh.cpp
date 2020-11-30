#include "TktkCollision/3D/BoundingMesh.h"

namespace tktkCollision
{
    BoundingMesh::BoundingMesh(const std::vector<std::vector<tktkMath::Vector3>>& mesh, const tktkMath::Vector3& centerPos)
        : m_basePolygonVertex(mesh)
    {
        for (auto& polygon : m_basePolygonVertex)
        {
            // �|���S���̒��_���R��菭�Ȃ��ꍇ�A���̃|���S����
            if (polygon.size() < 3U) continue;

            // �|���S���̒��S���W���v�Z����
            auto polyCenterPos = tktkMath::Vector3_v::zero;
            for (const auto& vertex : polygon) polyCenterPos += vertex;
            polyCenterPos /= polygon.size();

            for (auto& vertex : polygon)
            {
                vertex += centerPos;

                // ���̖ʂƔ��Ȃ��悤�Ƀ|���S���������k������
                vertex += (polyCenterPos - vertex).normalized() * 0.01f;
            }
        }
        m_transformedPolygonVertex = m_basePolygonVertex;
    }

    void BoundingMesh::transform(const tktkMath::Matrix4& worldMatrix)
    {
        for (size_t i = 0U; i < m_basePolygonVertex.size(); i++)
        {
        	for (size_t j = 0U; j < m_basePolygonVertex.at(i).size(); j++)
        	{
                m_transformedPolygonVertex.at(i).at(j) = m_basePolygonVertex.at(i).at(j) * worldMatrix;
        	}
        }
    }

    const std::vector<std::vector<tktkMath::Vector3>>& BoundingMesh::getBasePolygonVertex() const
    {
        return m_basePolygonVertex;
    }

    const std::vector<std::vector<tktkMath::Vector3>>& BoundingMesh::getTransformedPolygonVertex() const
    {
        return m_transformedPolygonVertex;
    }
}