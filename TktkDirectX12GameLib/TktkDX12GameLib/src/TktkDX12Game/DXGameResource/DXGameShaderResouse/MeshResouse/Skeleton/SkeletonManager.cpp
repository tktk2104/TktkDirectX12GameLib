#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/MeshResouse/Skeleton/SkeletonManager.h"

#include "TktkDX12Game/_MainManager/DX12GameManager.h"
#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/MeshResouse/Skeleton/BoneMatrixCbufferData.h"

namespace tktk
{
    SkeletonManager::SkeletonManager(const tktkContainer::ResourceContainerInitParam& initParam)
        : m_skeletonArray(initParam)
    {
        BoneMatrixCbufferData boneMatBuf;

        // 骨情報の定数バッファを単位行列でクリアする為のアップロードバッファを作りハンドルを取得する
        for (size_t i = 0; i < 128U; i++)
        {
            boneMatBuf.boneMatrix[i] = tktkMath::Matrix4_v::identity;
        }
        m_resetBoneMatrixUploadBufferHandle = DX12GameManager::createUploadBuffer(UploadBufferInitParam::create(BufferType::constant, DX12GameManager::getSystemHandle(SystemCBufferType::BoneMatCbuffer), boneMatBuf));
    }

    SkeletonManager::~SkeletonManager()
    {
        // 骨情報の定数バッファを単位行列でクリアする為のアップロードバッファを削除する
        DX12GameManager::eraseUploadBuffer(m_resetBoneMatrixUploadBufferHandle);
    }

    size_t SkeletonManager::create(const SkeletonInitParam& initParam)
    {
        return m_skeletonArray.create(initParam);
    }

    size_t SkeletonManager::copy(size_t originalHandle)
    {
        return m_skeletonArray.create(*m_skeletonArray.getMatchHandlePtr(originalHandle));
    }

    size_t SkeletonManager::createUploadBufferHandle(size_t handle) const
    {
        return m_skeletonArray.getMatchHandlePtr(handle)->createUploadBufferHandle();
    }

    void SkeletonManager::transform(size_t handle, const std::vector<MotionBoneParam>& transformMatrices)
    {
        m_skeletonArray.getMatchHandlePtr(handle)->transform(transformMatrices);
    }

    std::array<tktkMath::Matrix4, 128U> SkeletonManager::getBoneMatrixArray(size_t handle) const
    {
        return  m_skeletonArray.getMatchHandlePtr(handle)->getBoneMatrixArray();
    }

    void SkeletonManager::updateBoneMatrixCbuffer(size_t handle, size_t copyBufferHandle) const
    {
        m_skeletonArray.getMatchHandlePtr(handle)->updateBoneMatrixCbuffer(copyBufferHandle);
    }

    void SkeletonManager::resetBoneMatrixCbuffer() const
    {
        //  骨情報の定数バッファに単位行列アップロードバッファの情報をコピーする
        DX12GameManager::copyBuffer(m_resetBoneMatrixUploadBufferHandle);
    }
}