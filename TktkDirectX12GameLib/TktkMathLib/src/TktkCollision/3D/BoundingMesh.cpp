#include "TktkCollision/3D/BoundingMesh.h"

namespace tktkCollision
{
    BoundingMesh::BoundingMesh(const std::vector<std::vector<tktkMath::Vector3>>& mesh, const tktkMath::Vector3& centerPos)
        : m_mesh(mesh)
    {
        for (auto& polygon : m_mesh)
        {
            // ポリゴンの頂点が３つより少ない場合、次のポリゴンに
            if (polygon.size() < 3U) continue;

            // ポリゴンの中心座標を計算する
            auto polyCenterPos = tktkMath::Vector3_v::zero;
            for (const auto& vertex : polygon) polyCenterPos += vertex;
            polyCenterPos /= polygon.size();

            for (auto& vertex : polygon)
            {
                vertex += centerPos;

                // 他の面と被らないようにポリゴンを少し縮小する
                vertex += (polyCenterPos - vertex).normalized() * 0.01f;
            }
        }
    }

    const std::vector<std::vector<tktkMath::Vector3>>& BoundingMesh::getVertexs() const
    {
        return m_mesh;
    }
}