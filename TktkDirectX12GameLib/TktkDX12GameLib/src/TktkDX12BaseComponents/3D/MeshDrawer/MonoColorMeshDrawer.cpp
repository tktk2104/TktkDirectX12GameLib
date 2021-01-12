#include "TktkDX12BaseComponents/3D/MeshDrawer/MonoColorMeshDrawer.h"

#include "TktkDX12BaseComponents/3D/Transform3D/Transform3D.h"
#include "TktkDX12BaseComponents/3D/MeshAnimator/MeshAnimator.h"
#include "TktkDX12Game/_MainManager/DX12GameManager.h"
#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/MeshResouse/Mesh/Structs/MonoColorInstanceVertData.h"

namespace tktk
{
    MonoColorMeshDrawer::MonoColorMeshDrawer(size_t meshHandle, size_t skeletonHandle, const tktkMath::Color& albedoColor, const tktkMath::Vector3& basePosition, const tktkMath::Vector3& baseScale, const tktkMath::Quaternion& baseRotation)
        : m_meshHandle(meshHandle)
        , m_skeletonHandle(skeletonHandle)
        , m_albedoColor(albedoColor)
        , m_basePosition(basePosition)
        , m_baseScale(baseScale)
        , m_baseRotation(baseRotation)
    {
    }

    void MonoColorMeshDrawer::start()
    {
        m_transform = getComponent<Transform3D>();

        if (m_transform.expired())
        {
            throw std::runtime_error("BasicMeshDrawer not found Transform3D");
        }

        m_animator = getComponent<MeshAnimator>();
    }

    void MonoColorMeshDrawer::afterCollide()
    {
        if (!m_animator.expired() && m_skeletonHandle != 0U) m_animator->transformSkeleton(m_skeletonHandle);

        auto instanceVertData = MonoColorInstanceVertData();

        // ���[���h�s��
        instanceVertData.worldMatrix = tktkMath::Matrix4::createTRS(
            m_basePosition + m_transform->getWorldPosition(),
            m_baseRotation * m_transform->getWorldRotation(),
            tktkMath::Vector3::scale(m_baseScale, m_transform->getWorldScaleRate())
        );

        instanceVertData.albedoColor = m_albedoColor;

        // �w��̃��b�V�����C���X�^���X�`�悷�鎞�Ɏg�p����l��ǉ�����
        DX12GameManager::addMeshInstanceVertParam(m_meshHandle, CopySourceDataCarrier(instanceVertData, 0U));

        // �����X�P���g�����ݒ肳��Ă�����
        if (m_skeletonHandle != 0U)
        {
            // �w��̃X�L�j���O���b�V�����C���X�^���X�`�悷�鎞�Ɏg�p���鍜�s���ǉ�����
            DX12GameManager::addMeshInstanceBoneMatrix(m_meshHandle, m_skeletonHandle);
        }
    }
}