#include "TktkCollision/3D/BoundingMesh.h"

namespace tktkCollision
{
    BoundingMesh::BoundingMesh(const std::vector<tktkMath::Vector3>& vertexs)
        : m_vertexs(vertexs)
    {
    }

    const std::vector<tktkMath::Vector3>& BoundingMesh::getVertexs() const
    {
        return m_vertexs;
    }
}