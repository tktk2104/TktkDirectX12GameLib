#include "TktkCollision/3D/BoundingMesh.h"

namespace tktkCollision
{
    BoundingMesh::BoundingMesh(const std::vector<std::vector<tktkMath::Vector3>>& mesh, const tktkMath::Vector3& centerPos)
        : m_mesh(mesh)
    {
        for (auto& polygon : m_mesh)
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
    }

    const std::vector<std::vector<tktkMath::Vector3>>& BoundingMesh::getVertexs() const
    {
        return m_mesh;
    }
}