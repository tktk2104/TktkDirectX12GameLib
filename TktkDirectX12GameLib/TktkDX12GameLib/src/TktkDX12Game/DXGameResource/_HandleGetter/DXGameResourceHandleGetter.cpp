#include "TktkDX12Game/DXGameResource/_HandleGetter/DXGameResourceHandleGetter.h"

namespace tktk
{
    size_t DXGameResourceHandleGetter::getSceneHandle(ResourceIdCarrier id) const
    {
        return m_sceneHandleMap.at(id);
    }

    size_t DXGameResourceHandleGetter::getSoundHandle(ResourceIdCarrier id) const
    {
        return m_soundHandleMap.at(id);
    }

    size_t DXGameResourceHandleGetter::getPostEffectMaterialHandle(ResourceIdCarrier id) const
    {
        return m_postEffectMaterialHandleMap.at(id);
    }

    size_t DXGameResourceHandleGetter::getSpriteMaterialHandle(ResourceIdCarrier id) const
    {
        return m_spriteMaterialHandleMap.at(id);
    }

    size_t DXGameResourceHandleGetter::getLine2DMaterialHandle(ResourceIdCarrier id) const
    {
        return m_line2DMaterialHandleMap.at(id);
    }

    size_t DXGameResourceHandleGetter::getBillboardMaterialHandle(ResourceIdCarrier id) const
    {
        return m_billboardMaterialHandleMap.at(id);
    }

    size_t DXGameResourceHandleGetter::getSkeletonHandle(ResourceIdCarrier id) const
    {
        return m_skeletonHandleMap.at(id);
    }

    size_t DXGameResourceHandleGetter::getMotionHandle(ResourceIdCarrier id) const
    {
        return m_motionHandleMap.at(id);
    }

    size_t DXGameResourceHandleGetter::getBasicMeshHandle(ResourceIdCarrier id) const
    {
        return m_basicMeshHandleMap.at(id);
    }

    size_t DXGameResourceHandleGetter::getBasicMeshMaterialHandle(ResourceIdCarrier id) const
    {
        return m_basicMeshMaterialHandleMap.at(id);
    }

    size_t DXGameResourceHandleGetter::getCameraHandle(ResourceIdCarrier id) const
    {
        return m_cameraMap.at(id);
    }

    size_t DXGameResourceHandleGetter::getLightHandle(ResourceIdCarrier id) const
    {
        return m_lightMap.at(id);
    }

    void DXGameResourceHandleGetter::setSceneHandle(ResourceIdCarrier id, size_t handle)
    {
        m_sceneHandleMap.emplace(id, handle);
    }

    void DXGameResourceHandleGetter::setSoundHandle(ResourceIdCarrier id, size_t handle)
    {
        m_soundHandleMap.emplace(id, handle);
    }

    void DXGameResourceHandleGetter::setPostEffectMaterialHandle(ResourceIdCarrier id, size_t handle)
    {
        m_postEffectMaterialHandleMap.emplace(id, handle);
    }

    void DXGameResourceHandleGetter::setSpriteMaterialHandle(ResourceIdCarrier id, size_t handle)
    {
        m_spriteMaterialHandleMap.emplace(id, handle);
    }

    void DXGameResourceHandleGetter::setLine2DMaterialHandle(ResourceIdCarrier id, size_t handle)
    {
        m_line2DMaterialHandleMap.emplace(id, handle);
    }

    void DXGameResourceHandleGetter::setBillboardMaterialHandle(ResourceIdCarrier id, size_t handle)
    {
        m_billboardMaterialHandleMap.emplace(id, handle);
    }

    void DXGameResourceHandleGetter::setSkeletonHandle(ResourceIdCarrier id, size_t handle)
    {
        m_skeletonHandleMap.emplace(id, handle);
    }

    void DXGameResourceHandleGetter::setMotionHandle(ResourceIdCarrier id, size_t handle)
    {
        m_motionHandleMap.emplace(id, handle);
    }

    void DXGameResourceHandleGetter::setBasicMeshHandle(ResourceIdCarrier id, size_t handle)
    {
        m_basicMeshHandleMap.emplace(id, handle);
    }

    void DXGameResourceHandleGetter::setBasicMeshMaterialHandle(ResourceIdCarrier id, size_t handle)
    {
        m_basicMeshMaterialHandleMap.emplace(id, handle);
    }

    void DXGameResourceHandleGetter::setCameraHandle(ResourceIdCarrier id, size_t handle)
    {
        m_cameraMap.emplace(id, handle);
    }

    void DXGameResourceHandleGetter::setLightHandle(ResourceIdCarrier id, size_t handle)
    {
        m_lightMap.emplace(id, handle);
    }
}