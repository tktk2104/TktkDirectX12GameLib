#include "TktkDX12Game/DXGameResource/_HandleGetter/DXGameResourceHandleGetter.h"

namespace tktk
{
    unsigned int DXGameResourceHandleGetter::getSceneHandle(int id) const
    {
        return m_sceneHandleMap.at(id);
    }

    unsigned int DXGameResourceHandleGetter::getSoundHandle(int id) const
    {
        return m_soundHandleMap.at(id);
    }

    unsigned int DXGameResourceHandleGetter::getPostEffectMaterialHandle(int id) const
    {
        return m_postEffectMaterialHandleMap.at(id);
    }

    unsigned int DXGameResourceHandleGetter::getSpriteMaterialHandle(int id) const
    {
        return m_spriteMaterialHandleMap.at(id);
    }

    unsigned int DXGameResourceHandleGetter::getLine2DMaterialHandle(int id) const
    {
        return m_line2DMaterialHandleMap.at(id);
    }

    unsigned int DXGameResourceHandleGetter::getBillboardMaterialHandle(int id) const
    {
        return m_billboardMaterialHandleMap.at(id);
    }

    unsigned int DXGameResourceHandleGetter::getSkeletonHandle(int id) const
    {
        return m_skeletonHandleMap.at(id);
    }

    unsigned int DXGameResourceHandleGetter::getMotionHandle(int id) const
    {
        return m_motionHandleMap.at(id);
    }

    unsigned int DXGameResourceHandleGetter::getBasicMeshHandle(int id) const
    {
        return m_basicMeshHandleMap.at(id);
    }

    unsigned int DXGameResourceHandleGetter::getBasicMeshMaterialHandle(int id) const
    {
        return m_basicMeshMaterialHandleMap.at(id);
    }

    unsigned int DXGameResourceHandleGetter::getCameraHandle(int id) const
    {
        return m_cameraMap.at(id);
    }

    unsigned int DXGameResourceHandleGetter::getLightHandle(int id) const
    {
        return m_lightMap.at(id);
    }

    void DXGameResourceHandleGetter::setSceneHandle(int id, unsigned int handle)
    {
        m_sceneHandleMap.emplace(id, handle);
    }

    void DXGameResourceHandleGetter::setSoundHandle(int id, unsigned int handle)
    {
        m_soundHandleMap.emplace(id, handle);
    }

    void DXGameResourceHandleGetter::setPostEffectMaterialHandle(int id, unsigned int handle)
    {
        m_postEffectMaterialHandleMap.emplace(id, handle);
    }

    void DXGameResourceHandleGetter::setSpriteMaterialHandle(int id, unsigned int handle)
    {
        m_spriteMaterialHandleMap.emplace(id, handle);
    }

    void DXGameResourceHandleGetter::setLine2DMaterialHandle(int id, unsigned int handle)
    {
        m_line2DMaterialHandleMap.emplace(id, handle);
    }

    void DXGameResourceHandleGetter::setBillboardMaterialHandle(int id, unsigned int handle)
    {
        m_billboardMaterialHandleMap.emplace(id, handle);
    }

    void DXGameResourceHandleGetter::setSkeletonHandle(int id, unsigned int handle)
    {
        m_skeletonHandleMap.emplace(id, handle);
    }

    void DXGameResourceHandleGetter::setMotionHandle(int id, unsigned int handle)
    {
        m_motionHandleMap.emplace(id, handle);
    }

    void DXGameResourceHandleGetter::setBasicMeshHandle(int id, unsigned int handle)
    {
        m_basicMeshHandleMap.emplace(id, handle);
    }

    void DXGameResourceHandleGetter::setBasicMeshMaterialHandle(int id, unsigned int handle)
    {
        m_basicMeshMaterialHandleMap.emplace(id, handle);
    }

    void DXGameResourceHandleGetter::setCameraHandle(int id, unsigned int handle)
    {
        m_cameraMap.emplace(id, handle);
    }

    void DXGameResourceHandleGetter::setLightHandle(int id, unsigned int handle)
    {
        m_lightMap.emplace(id, handle);
    }
}