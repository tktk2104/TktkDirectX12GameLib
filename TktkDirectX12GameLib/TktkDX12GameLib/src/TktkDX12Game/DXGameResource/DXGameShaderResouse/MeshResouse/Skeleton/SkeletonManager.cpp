#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/MeshResouse/Skeleton/SkeletonManager.h"

#include "TktkDX12Game/_MainManager/DX12GameManager.h"

namespace tktk
{
    SkeletonManager::SkeletonManager(const tktkContainer::ResourceContainerInitParam& initParam)
        : m_skeletonArray(initParam)
    {
    }

    // デストラクタの非インライン化
    SkeletonManager::~SkeletonManager() = default;

    size_t SkeletonManager::create(const SkeletonInitParam& initParam)
    {
        return m_skeletonArray.create(initParam);
    }

    size_t SkeletonManager::copy(size_t originalHandle)
    {
        return m_skeletonArray.create(*m_skeletonArray.getMatchHandlePtr(originalHandle));
    }

    void SkeletonManager::transform(size_t handle, const std::vector<MotionBoneParam>& transformMatrices)
    {
        m_skeletonArray.getMatchHandlePtr(handle)->transform(transformMatrices);
    }

    std::array<tktkMath::Matrix4, 128U> SkeletonManager::getBoneMatrixArray(size_t handle) const
    {
        return  m_skeletonArray.getMatchHandlePtr(handle)->getBoneMatrixArray();
    }
}