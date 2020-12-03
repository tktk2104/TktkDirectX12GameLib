#include "TktkDX12Game/UtilityProcessManager/ResourceHandleGetter/ResourceIdConverter/ResourceIdConverter.h"

namespace tktk
{
    // デストラクタを非インライン化する
    ResourceIdConverter::~ResourceIdConverter() = default;

    size_t ResourceIdConverter::getSceneHandle(ResourceIdCarrier id) const
    {
        return m_sceneHandleMap.at(id);
    }

    size_t ResourceIdConverter::getSoundHandle(ResourceIdCarrier id) const
    {
        return m_soundHandleMap.at(id);
    }

    size_t ResourceIdConverter::getPostEffectMaterialHandle(ResourceIdCarrier id) const
    {
        return m_postEffectMaterialHandleMap.at(id);
    }

    size_t ResourceIdConverter::getSpriteMaterialHandle(ResourceIdCarrier id) const
    {
        return m_spriteMaterialHandleMap.at(id);
    }

    size_t ResourceIdConverter::getLine2DMaterialHandle(ResourceIdCarrier id) const
    {
        return m_line2DMaterialHandleMap.at(id);
    }

    size_t ResourceIdConverter::getBillboardMaterialHandle(ResourceIdCarrier id) const
    {
        return m_billboardMaterialHandleMap.at(id);
    }

    size_t ResourceIdConverter::getSkeletonHandle(ResourceIdCarrier id) const
    {
        return m_skeletonHandleMap.at(id);
    }

    size_t ResourceIdConverter::getMotionHandle(ResourceIdCarrier id) const
    {
        return m_motionHandleMap.at(id);
    }

    size_t ResourceIdConverter::getBasicMeshHandle(ResourceIdCarrier id) const
    {
        return m_basicMeshHandleMap.at(id);
    }

    size_t ResourceIdConverter::getBasicMeshMaterialHandle(ResourceIdCarrier id) const
    {
        return m_basicMeshMaterialHandleMap.at(id);
    }

    size_t ResourceIdConverter::getCameraHandle(ResourceIdCarrier id) const
    {
        return m_cameraMap.at(id);
    }

    size_t ResourceIdConverter::getLightHandle(ResourceIdCarrier id) const
    {
        return m_lightMap.at(id);
    }

    void ResourceIdConverter::setSceneHandle(ResourceIdCarrier id, size_t handle)
    {
        m_sceneHandleMap.emplace(id, handle);
    }

    void ResourceIdConverter::setSoundHandle(ResourceIdCarrier id, size_t handle)
    {
        m_soundHandleMap.emplace(id, handle);
    }

    void ResourceIdConverter::setPostEffectMaterialHandle(ResourceIdCarrier id, size_t handle)
    {
        m_postEffectMaterialHandleMap.emplace(id, handle);
    }

    void ResourceIdConverter::setSpriteMaterialHandle(ResourceIdCarrier id, size_t handle)
    {
        m_spriteMaterialHandleMap.emplace(id, handle);
    }

    void ResourceIdConverter::setLine2DMaterialHandle(ResourceIdCarrier id, size_t handle)
    {
        m_line2DMaterialHandleMap.emplace(id, handle);
    }

    void ResourceIdConverter::setBillboardMaterialHandle(ResourceIdCarrier id, size_t handle)
    {
        m_billboardMaterialHandleMap.emplace(id, handle);
    }

    void ResourceIdConverter::setSkeletonHandle(ResourceIdCarrier id, size_t handle)
    {
        m_skeletonHandleMap.emplace(id, handle);
    }

    void ResourceIdConverter::setMotionHandle(ResourceIdCarrier id, size_t handle)
    {
        m_motionHandleMap.emplace(id, handle);
    }

    void ResourceIdConverter::setMeshHandle(ResourceIdCarrier id, size_t handle)
    {
        m_basicMeshHandleMap.emplace(id, handle);
    }

    void ResourceIdConverter::setMeshMaterialHandle(ResourceIdCarrier id, size_t handle)
    {
        m_basicMeshMaterialHandleMap.emplace(id, handle);
    }

    void ResourceIdConverter::setCameraHandle(ResourceIdCarrier id, size_t handle)
    {
        m_cameraMap.emplace(id, handle);
    }

    void ResourceIdConverter::setLightHandle(ResourceIdCarrier id, size_t handle)
    {
        m_lightMap.emplace(id, handle);
    }
}