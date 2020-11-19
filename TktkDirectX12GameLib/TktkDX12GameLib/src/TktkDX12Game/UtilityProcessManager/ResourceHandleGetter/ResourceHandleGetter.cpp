#include "TktkDX12Game/UtilityProcessManager/ResourceHandleGetter/ResourceHandleGetter.h"

#include "TktkDX12Game/UtilityProcessManager/ResourceHandleGetter/SystemResourceHandleGetter/SystemResourceHandleGetter.h"
#include "TktkDX12Game/UtilityProcessManager/ResourceHandleGetter/ResourceIdConverter/ResourceIdConverter.h"

namespace tktk
{
    ResourceHandleGetter::ResourceHandleGetter()
    {
        m_systemResouseHandleGetter = std::make_unique<SystemResourceHandleGetter>();
        m_resourceIdConverter       = std::make_unique<ResourceIdConverter>();
    }

    // デストラクタを非インライン化する
    ResourceHandleGetter::~ResourceHandleGetter() = default;

    size_t ResourceHandleGetter::getSystemHandle(SystemViewportType type) const
    {
        return m_systemResouseHandleGetter->getSystemHandle(type);
    }

    size_t ResourceHandleGetter::getSystemHandle(SystemScissorRectType type) const
    {
        return m_systemResouseHandleGetter->getSystemHandle(type);
    }

    size_t ResourceHandleGetter::getSystemHandle(SystemVertexBufferType type) const
    {
        return m_systemResouseHandleGetter->getSystemHandle(type);
    }

    size_t ResourceHandleGetter::getSystemHandle(SystemIndexBufferType type) const
    {
        return m_systemResouseHandleGetter->getSystemHandle(type);
    }

    size_t ResourceHandleGetter::getSystemHandle(SystemCBufferType type) const
    {
        return m_systemResouseHandleGetter->getSystemHandle(type);
    }

    size_t ResourceHandleGetter::getSystemHandle(SystemTextureBufferType type) const
    {
        return m_systemResouseHandleGetter->getSystemHandle(type);
    }

    size_t ResourceHandleGetter::getSystemHandle(SystemRtBufferType type) const
    {
        return m_systemResouseHandleGetter->getSystemHandle(type);
    }

    size_t ResourceHandleGetter::getSystemHandle(SystemDsBufferType type) const
    {
        return m_systemResouseHandleGetter->getSystemHandle(type);
    }

    size_t ResourceHandleGetter::getSystemHandle(SystemBasicDescriptorHeapType type) const
    {
        return m_systemResouseHandleGetter->getSystemHandle(type);
    }

    size_t ResourceHandleGetter::getSystemHandle(SystemRtvDescriptorHeapType type) const
    {
        return m_systemResouseHandleGetter->getSystemHandle(type);
    }

    size_t ResourceHandleGetter::getSystemHandle(SystemDsvDescriptorHeapType type) const
    {
        return m_systemResouseHandleGetter->getSystemHandle(type);
    }

    size_t ResourceHandleGetter::getSystemHandle(SystemRootSignatureType type) const
    {
        return m_systemResouseHandleGetter->getSystemHandle(type);
    }

    size_t ResourceHandleGetter::getSystemHandle(SystemPipeLineStateType type) const
    {
        return m_systemResouseHandleGetter->getSystemHandle(type);
    }

    size_t ResourceHandleGetter::getSystemHandle(SystemCameraType type) const
    {
        return m_systemResouseHandleGetter->getSystemHandle(type);
    }

    size_t ResourceHandleGetter::getSystemHandle(SystemLightType type) const
    {
        return m_systemResouseHandleGetter->getSystemHandle(type);
    }

    size_t ResourceHandleGetter::getSystemHandle(SystemMeshType type) const
    {
        return m_systemResouseHandleGetter->getSystemHandle(type);
    }

    size_t ResourceHandleGetter::getSystemHandle(SystemMeshMaterialType type) const
    {
        return m_systemResouseHandleGetter->getSystemHandle(type);
    }

    size_t ResourceHandleGetter::getSystemHandle(SystemPostEffectMaterialType type) const
    {
        return m_systemResouseHandleGetter->getSystemHandle(type);
    }

    void ResourceHandleGetter::setSystemHandle(SystemViewportType type, size_t handle)
    {
        m_systemResouseHandleGetter->setSystemHandle(type, handle);
    }

    void ResourceHandleGetter::setSystemHandle(SystemScissorRectType type, size_t handle)
    {
        m_systemResouseHandleGetter->setSystemHandle(type, handle);
    }

    void ResourceHandleGetter::setSystemHandle(SystemVertexBufferType type, size_t handle)
    {
        m_systemResouseHandleGetter->setSystemHandle(type, handle);
    }

    void ResourceHandleGetter::setSystemHandle(SystemIndexBufferType type, size_t handle)
    {
        m_systemResouseHandleGetter->setSystemHandle(type, handle);
    }

    void ResourceHandleGetter::setSystemHandle(SystemCBufferType type, size_t handle)
    {
        m_systemResouseHandleGetter->setSystemHandle(type, handle);
    }

    void ResourceHandleGetter::setSystemHandle(SystemTextureBufferType type, size_t handle)
    {
        m_systemResouseHandleGetter->setSystemHandle(type, handle);
    }

    void ResourceHandleGetter::setSystemHandle(SystemRtBufferType type, size_t handle)
    {
        m_systemResouseHandleGetter->setSystemHandle(type, handle);
    }

    void ResourceHandleGetter::setSystemHandle(SystemDsBufferType type, size_t handle)
    {
        m_systemResouseHandleGetter->setSystemHandle(type, handle);
    }

    void ResourceHandleGetter::setSystemHandle(SystemBasicDescriptorHeapType type, size_t handle)
    {
        m_systemResouseHandleGetter->setSystemHandle(type, handle);
    }

    void ResourceHandleGetter::setSystemHandle(SystemRtvDescriptorHeapType type, size_t handle)
    {
        m_systemResouseHandleGetter->setSystemHandle(type, handle);
    }

    void ResourceHandleGetter::setSystemHandle(SystemDsvDescriptorHeapType type, size_t handle)
    {
        m_systemResouseHandleGetter->setSystemHandle(type, handle);
    }

    void ResourceHandleGetter::setSystemHandle(SystemRootSignatureType type, size_t handle)
    {
        m_systemResouseHandleGetter->setSystemHandle(type, handle);
    }

    void ResourceHandleGetter::setSystemHandle(SystemPipeLineStateType type, size_t handle)
    {
        m_systemResouseHandleGetter->setSystemHandle(type, handle);
    }

    void ResourceHandleGetter::setSystemHandle(SystemCameraType type, size_t handle)
    {
        m_systemResouseHandleGetter->setSystemHandle(type, handle);
    }

    void ResourceHandleGetter::setSystemHandle(SystemLightType type, size_t handle)
    {
        m_systemResouseHandleGetter->setSystemHandle(type, handle);
    }

    void ResourceHandleGetter::setSystemHandle(SystemMeshType type, size_t handle)
    {
        m_systemResouseHandleGetter->setSystemHandle(type, handle);
    }

    void ResourceHandleGetter::setSystemHandle(SystemMeshMaterialType type, size_t handle)
    {
        m_systemResouseHandleGetter->setSystemHandle(type, handle);
    }

    void ResourceHandleGetter::setSystemHandle(SystemPostEffectMaterialType type, size_t handle)
    {
        m_systemResouseHandleGetter->setSystemHandle(type, handle);
    }

    size_t ResourceHandleGetter::getSceneHandle(ResourceIdCarrier id) const
    {
        return m_resourceIdConverter->getSceneHandle(id);
    }

    size_t ResourceHandleGetter::getSoundHandle(ResourceIdCarrier id) const
    {
        return m_resourceIdConverter->getSoundHandle(id);
    }

    size_t ResourceHandleGetter::getPostEffectMaterialHandle(ResourceIdCarrier id) const
    {
        return m_resourceIdConverter->getPostEffectMaterialHandle(id);
    }

    size_t ResourceHandleGetter::getSpriteMaterialHandle(ResourceIdCarrier id) const
    {
        return m_resourceIdConverter->getSpriteMaterialHandle(id);
    }

    size_t ResourceHandleGetter::getLine2DMaterialHandle(ResourceIdCarrier id) const
    {
        return m_resourceIdConverter->getLine2DMaterialHandle(id);
    }

    size_t ResourceHandleGetter::getBillboardMaterialHandle(ResourceIdCarrier id) const
    {
        return m_resourceIdConverter->getBillboardMaterialHandle(id);
    }

    size_t ResourceHandleGetter::getSkeletonHandle(ResourceIdCarrier id) const
    {
        return m_resourceIdConverter->getSkeletonHandle(id);
    }

    size_t ResourceHandleGetter::getMotionHandle(ResourceIdCarrier id) const
    {
        return m_resourceIdConverter->getMotionHandle(id);
    }

    size_t ResourceHandleGetter::getBasicMeshHandle(ResourceIdCarrier id) const
    {
        return m_resourceIdConverter->getBasicMeshHandle(id);
    }

    size_t ResourceHandleGetter::getBasicMeshMaterialHandle(ResourceIdCarrier id) const
    {
        return m_resourceIdConverter->getBasicMeshMaterialHandle(id);
    }

    size_t ResourceHandleGetter::getCameraHandle(ResourceIdCarrier id) const
    {
        return m_resourceIdConverter->getCameraHandle(id);
    }

    size_t ResourceHandleGetter::getLightHandle(ResourceIdCarrier id) const
    {
        return m_resourceIdConverter->getLightHandle(id);
    }

    void ResourceHandleGetter::setSceneHandle(ResourceIdCarrier id, size_t handle)
    {
        m_resourceIdConverter->setSceneHandle(id, handle);
    }

    void ResourceHandleGetter::setSoundHandle(ResourceIdCarrier id, size_t handle)
    {
        m_resourceIdConverter->setSoundHandle(id, handle);
    }

    void ResourceHandleGetter::setPostEffectMaterialHandle(ResourceIdCarrier id, size_t handle)
    {
        m_resourceIdConverter->setPostEffectMaterialHandle(id, handle);
    }

    void ResourceHandleGetter::setSpriteMaterialHandle(ResourceIdCarrier id, size_t handle)
    {
        m_resourceIdConverter->setSpriteMaterialHandle(id, handle);
    }

    void ResourceHandleGetter::setLine2DMaterialHandle(ResourceIdCarrier id, size_t handle)
    {
        m_resourceIdConverter->setLine2DMaterialHandle(id, handle);
    }

    void ResourceHandleGetter::setBillboardMaterialHandle(ResourceIdCarrier id, size_t handle)
    {
        m_resourceIdConverter->setBillboardMaterialHandle(id, handle);
    }

    void ResourceHandleGetter::setSkeletonHandle(ResourceIdCarrier id, size_t handle)
    {
        m_resourceIdConverter->setSkeletonHandle(id, handle);
    }

    void ResourceHandleGetter::setMotionHandle(ResourceIdCarrier id, size_t handle)
    {
        m_resourceIdConverter->setMotionHandle(id, handle);
    }

    void ResourceHandleGetter::setMeshHandle(ResourceIdCarrier id, size_t handle)
    {
        m_resourceIdConverter->setMeshHandle(id, handle);
    }

    void ResourceHandleGetter::setMeshMaterialHandle(ResourceIdCarrier id, size_t handle)
    {
        m_resourceIdConverter->setMeshMaterialHandle(id, handle);
    }

    void ResourceHandleGetter::setCameraHandle(ResourceIdCarrier id, size_t handle)
    {
        m_resourceIdConverter->setCameraHandle(id, handle);
    }

    void ResourceHandleGetter::setLightHandle(ResourceIdCarrier id, size_t handle)
    {
        m_resourceIdConverter->setLightHandle(id, handle);
    }
}