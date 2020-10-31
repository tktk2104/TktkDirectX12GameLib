#include "TktkCollision/3D/BoundingMesh.h"

namespace tktkCollision
{
    BoundingMesh::BoundingMesh(const std::vector<std::vector<tktkMath::Vector3>>& mesh, const tktkMath::Vector3& centerPos)
        : m_mesh(mesh)
    {
        for (auto& polygon : m_mesh)
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
    }

    const std::vector<std::vector<tktkMath::Vector3>>& BoundingMesh::getVertexs() const
    {
        return m_mesh;
    }
}