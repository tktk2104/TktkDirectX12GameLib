#include "TktkDX12Game/DXGameResource/Mesh/Skeleton/Skeleton.h"

#include "TktkDX12Game/_MainManager/DX12GameManager.h"
#include "TktkDX12Game/DXGameResource/Mesh/Skeleton/BoneMatrixCbufferData.h"

namespace tktk
{
    Skeleton::Skeleton(const tktkContainer::ResourceContainerInitParam& initParam)
        : m_skeletonArray(initParam)
    {
        DX12GameManager::setSystemHandle(SystemCBufferType::BoneMatCbuffer, DX12GameManager::createCBuffer(BoneMatrixCbufferData()));
    
        BoneMatrixCbufferData boneMatBuf;

        // 骨情報の定数バッファを単位行列でクリアする為のコピーバッファを作りハンドルを取得する
        for (unsigned int i = 0; i < 128U; i++)
        {
            boneMatBuf.boneMatrix[i] = tktkMath::Matrix4_v::identity;
        }
        m_resetBoneMatrixCopyBufferHandle = DX12GameManager::createCopyBuffer(BufferType::constant, DX12GameManager::getSystemHandle(SystemCBufferType::BoneMatCbuffer), boneMatBuf);
    }

    Skeleton::~Skeleton()
    {
        // 骨情報の定数バッファを単位行列でクリアする為のコピーバッファを削除する
        DX12GameManager::eraseCopyBuffer(m_resetBoneMatrixCopyBufferHandle);
    }

    unsigned int Skeleton::create(const SkeletonInitParam& initParam)
    {
        return m_skeletonArray.create(initParam);
    }

    unsigned int Skeleton::copy(unsigned int originalHandle)
    {
        return m_skeletonArray.create(*m_skeletonArray.getMatchHandlePtr(originalHandle));
    }

    unsigned int Skeleton::createCopyBufferHandle(unsigned int handle) const
    {
        return m_skeletonArray.getMatchHandlePtr(handle)->createCopyBufferHandle();
    }

    void Skeleton::transform(unsigned int handle, const std::vector<MotionBoneParam>& transformMatrices)
    {
        m_skeletonArray.getMatchHandlePtr(handle)->transform(transformMatrices);
    }

    void Skeleton::updateBoneMatrixCbuffer(unsigned int handle, unsigned int copyBufferHandle) const
    {
        m_skeletonArray.getMatchHandlePtr(handle)->updateBoneMatrixCbuffer(copyBufferHandle);
    }

    void Skeleton::resetBoneMatrixCbuffer() const
    {
        //  骨情報の定数バッファに単位行列コピーバッファの情報をコピーする
        DX12GameManager::copyBuffer(m_resetBoneMatrixCopyBufferHandle);
    }
}