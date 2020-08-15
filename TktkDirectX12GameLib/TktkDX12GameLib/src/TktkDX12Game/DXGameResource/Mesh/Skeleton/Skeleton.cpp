#include "TktkDX12Game/DXGameResource/Mesh/Skeleton/Skeleton.h"

#include "TktkDX12Game/_MainManager/DX12GameManager.h"
#include "TktkDX12Game/DXGameResource/Mesh/Skeleton/BoneMatrixCbufferData.h"

namespace tktk
{
    Skeleton::Skeleton(unsigned int skeletonNum)
        : m_skeletonArray(skeletonNum)
    {
        DX12GameManager::createCBuffer(DX12GameManager::getSystemId(SystemCBufferType::BoneMatCbuffer), BoneMatrixCbufferData());
    }

    void Skeleton::create(unsigned int id, const SkeletonInitParam& initParam)
    {
        m_skeletonArray.emplaceAt(id, initParam);
    }

    void Skeleton::transform(unsigned int id, const std::vector<MotionBoneParam>& transformMatrices)
    {
        m_skeletonArray.at(id)->transform(transformMatrices);
    }

    void Skeleton::updateBoneMatrixCbuffer(unsigned int id) const
    {
        m_skeletonArray.at(id)->updateBoneMatrixCbuffer();
    }

    void Skeleton::resetBoneMatrixCbuffer() const
    {
        BoneMatrixCbufferData boneMatBuf;

        // 骨情報の定数バッファを単位行列でクリアする
        for (unsigned int i = 0; i < 128U; i++)
        {
            boneMatBuf.boneMatrix[i] = tktkMath::Matrix4_v::identity;
        }

        // 骨情報の定数バッファを更新する
        DX12GameManager::updateCBuffer(DX12GameManager::getSystemId(SystemCBufferType::BoneMatCbuffer), boneMatBuf);
    }
}