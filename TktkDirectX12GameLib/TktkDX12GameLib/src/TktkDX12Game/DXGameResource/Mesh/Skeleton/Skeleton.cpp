#include "TktkDX12Game/DXGameResource/Mesh/Skeleton/Skeleton.h"

#include "TktkDX12Game/_MainManager/DX12GameManager.h"
#include "TktkDX12Game/DXGameResource/Mesh/Skeleton/BoneMatrixCbufferData.h"

namespace tktk
{
    Skeleton::Skeleton(const tktkContainer::ResourceContainerInitParam& initParam)
        : m_skeletonArray(initParam)
    {
        DX12GameManager::setSystemHandle(SystemCBufferType::BoneMatCbuffer, DX12GameManager::createCBuffer(BoneMatrixCbufferData()));
    }

    unsigned int Skeleton::create(const SkeletonInitParam& initParam)
    {
        return m_skeletonArray.create(initParam);
    }

    void Skeleton::transform(unsigned int handle, const std::vector<MotionBoneParam>& transformMatrices)
    {
        m_skeletonArray.getMatchHandlePtr(handle)->transform(transformMatrices);
    }

    void Skeleton::updateBoneMatrixCbuffer(unsigned int handle) const
    {
        m_skeletonArray.getMatchHandlePtr(handle)->updateBoneMatrixCbuffer();
    }

    void Skeleton::resetBoneMatrixCbuffer() const
    {
        BoneMatrixCbufferData boneMatBuf;

        // �����̒萔�o�b�t�@��P�ʍs��ŃN���A����
        for (unsigned int i = 0; i < 128U; i++)
        {
            boneMatBuf.boneMatrix[i] = tktkMath::Matrix4_v::identity;
        }

        // �����̒萔�o�b�t�@���X�V����
        DX12GameManager::updateCBuffer(DX12GameManager::getSystemHandle(SystemCBufferType::BoneMatCbuffer), boneMatBuf);
    }
}