#include "TktkCollision/3D/BoundingMesh.h"

namespace tktkCollision
{
    BoundingMesh::BoundingMesh(const std::vector<std::vector<tktkMath::Vector3>>& mesh, const tktkMath::Vector3& centerPos)
        : m_basePolygonVertex(mesh)
    {
        for (auto& polygon : m_basePolygonVertex)
        {
            // ƒ|ƒŠƒSƒ“‚Ì’¸“_‚ª‚R‚Â‚æ‚è­‚È‚¢ê‡AŸ‚Ìƒ|ƒŠƒSƒ“‚É
            if (polygon.size() < 3U) continue;

            // ƒ|ƒŠƒSƒ“‚Ì’†SÀ•W‚ğŒvZ‚·‚é
            auto polyCenterPos = tktkMath::Vector3_v::zero;
            for (const auto& vertex : polygon) polyCenterPos += vertex;
            polyCenterPos /= polygon.size();

            for (auto& vertex : polygon)
            {
                vertex += centerPos;

                // ‘¼‚Ì–Ê‚Æ”í‚ç‚È‚¢‚æ‚¤‚Éƒ|ƒŠƒSƒ“‚ğ­‚µk¬‚·‚é
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