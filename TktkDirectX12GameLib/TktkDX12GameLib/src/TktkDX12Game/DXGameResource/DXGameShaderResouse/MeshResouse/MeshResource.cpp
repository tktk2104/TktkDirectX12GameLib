#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/MeshResouse/MeshResource.h"

#include <TktkDX12Game/_MainManager/DX12GameManager.h>
#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/MeshResouse/Skeleton/SkeletonManager.h"
#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/MeshResouse/Motion/MotionManager.h"
#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/MeshResouse/Motion/MotionBoneParam.h"
#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/MeshResouse/Mesh/MeshManager.h"
#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/MeshResouse/MeshMaterial/MeshMaterialManager.h"
#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/MeshResouse/Mesh/Loader/MeshPmdLoader.h"
#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/MeshResouse/Mesh/Loader/MeshPmxLoader.h"
#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/MeshResouse/Structs/MeshResourceInitParam.h"

namespace tktk
{
    MeshResource::MeshResource(const MeshResourceInitParam& initParam)
    {
        // 各種リソースクラスを作る
        m_skeleton              = std::make_unique<SkeletonManager>(initParam.skeletonMgrParam);
        m_motion                = std::make_unique<MotionManager>(initParam.motionMgrParam);
        m_meshManager           = std::make_unique<MeshManager>(initParam.meshMgrParam);
        m_meshMaterialManager   = std::make_unique<MeshMaterialManager>(initParam.meshMatMgrParam);
    }

    // デストラクタを非インライン化する
    MeshResource::~MeshResource() = default;

    size_t MeshResource::createSkeleton(const SkeletonInitParam& initParam)
    {
        return m_skeleton->create(initParam);
    }

    size_t MeshResource::copySkeleton(size_t originalHandle)
    {
        return m_skeleton->copy(originalHandle);
    }

    size_t MeshResource::createSkeletonUploadBufferHandle(size_t handle) const
    {
        return m_skeleton->createUploadBufferHandle(handle);
    }

    void MeshResource::updateBoneMatrixCbuffer(size_t handle, size_t copyBufferHandle) const
    {
        m_skeleton->updateBoneMatrixCbuffer(handle, copyBufferHandle);
    }

    void MeshResource::resetBoneMatrixCbuffer() const
    {
        m_skeleton->resetBoneMatrixCbuffer();
    }

    size_t MeshResource::loadMotion(const std::string& motionFileName)
    {
        return m_motion->load(motionFileName);
    }

    size_t MeshResource::getMotionEndFrameNo(size_t handle) const
    {
        return m_motion->getEndFrameNo(handle);
    }

    void MeshResource::updateMotion(size_t skeletonHandle, size_t curMotionHandle, size_t preMotionHandle, size_t curFrame, size_t preFrame, float amount)
    {
        m_skeleton->transform(skeletonHandle, m_motion->calculateBoneTransformMatrices(curMotionHandle, preMotionHandle, curFrame, preFrame, amount));
    }

    size_t MeshResource::createBasicMesh(const MeshInitParam& initParam)
    {
        return m_meshManager->craete(initParam);
    }

    size_t MeshResource::copyBasicMesh(size_t originalHandle)
    {
        return m_meshManager->copy(originalHandle);
    }

    size_t MeshResource::createBasicMeshMaterial(const MeshMaterialInitParam& initParam)
    {
        return m_meshMaterialManager->create(initParam);
    }

    size_t MeshResource::copyBasicMeshMaterial(size_t originalHandle)
    {
        return m_meshMaterialManager->copy(originalHandle);
    }

    void MeshResource::setMaterialHandle(size_t meshHandle, size_t materialSlot, size_t materialHandle)
    {
        m_meshManager->setMaterialHandle(meshHandle, materialSlot, materialHandle);
    }

    void MeshResource::writeBasicMeshShadowMap(size_t handle) const
    {
        m_meshManager->writeShadowMap(handle);
    }

    void MeshResource::setMaterialData(size_t handle) const
    {
        m_meshMaterialManager->setMaterialData(handle);
    }

    void MeshResource::addMaterialAppendParam(size_t handle, const MeshMaterialAppendParamInitParam& initParam)
    {
        m_meshMaterialManager->addAppendParam(handle, initParam);
    }

    void MeshResource::updateMaterialAppendParam(size_t handle, const MeshMaterialAppendParamUpdateFuncArgs& updateFuncArgs)
    {
        m_meshMaterialManager->updateAppendParam(handle, updateFuncArgs);
    }

    void MeshResource::drawBasicMesh(size_t handle, const MeshDrawFuncBaseArgs& baseArgs) const
    {
        m_meshManager->drawMesh(handle, baseArgs);
    }

    MeshLoadPmdReturnValue MeshResource::loadPmd(const MeshLoadPmdArgs& args)
    {
        return MeshPmdLoader::loadPmd(args);
    }

    MeshLoadPmxReturnValue MeshResource::loadPmx(const MeshLoadPmxArgs& args)
    {
        return MeshPmxLoader::loadPmx(args);
    }
}