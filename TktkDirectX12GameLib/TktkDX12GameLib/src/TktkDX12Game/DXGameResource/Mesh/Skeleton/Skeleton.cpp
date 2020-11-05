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

        // �����̒萔�o�b�t�@��P�ʍs��ŃN���A����ׂ̃A�b�v���[�h�o�b�t�@�����n���h�����擾����
        for (size_t i = 0; i < 128U; i++)
        {
            boneMatBuf.boneMatrix[i] = tktkMath::Matrix4_v::identity;
        }
        m_resetBoneMatrixUploadBufferHandle = DX12GameManager::createUploadBuffer(UploadBufferInitParam::create(BufferType::constant, DX12GameManager::getSystemHandle(SystemCBufferType::BoneMatCbuffer), boneMatBuf));
    }

    Skeleton::~Skeleton()
    {
        // �����̒萔�o�b�t�@��P�ʍs��ŃN���A����ׂ̃A�b�v���[�h�o�b�t�@���폜����
        DX12GameManager::eraseUploadBuffer(m_resetBoneMatrixUploadBufferHandle);
    }

    size_t Skeleton::create(const SkeletonInitParam& initParam)
    {
        return m_skeletonArray.create(initParam);
    }

    size_t Skeleton::copy(size_t originalHandle)
    {
        return m_skeletonArray.create(*m_skeletonArray.getMatchHandlePtr(originalHandle));
    }

    size_t Skeleton::createUploadBufferHandle(size_t handle) const
    {
        return m_skeletonArray.getMatchHandlePtr(handle)->createUploadBufferHandle();
    }

    void Skeleton::transform(size_t handle, const std::vector<MotionBoneParam>& transformMatrices)
    {
        m_skeletonArray.getMatchHandlePtr(handle)->transform(transformMatrices);
    }

    void Skeleton::updateBoneMatrixCbuffer(size_t handle, size_t copyBufferHandle) const
    {
        m_skeletonArray.getMatchHandlePtr(handle)->updateBoneMatrixCbuffer(copyBufferHandle);
    }

    void Skeleton::resetBoneMatrixCbuffer() const
    {
        //  �����̒萔�o�b�t�@�ɒP�ʍs��A�b�v���[�h�o�b�t�@�̏����R�s�[����
        DX12GameManager::copyBuffer(m_resetBoneMatrixUploadBufferHandle);
    }
}