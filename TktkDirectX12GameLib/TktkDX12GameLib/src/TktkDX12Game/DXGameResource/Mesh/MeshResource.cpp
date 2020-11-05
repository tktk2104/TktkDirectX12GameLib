#include "TktkDX12Game/DXGameResource/Mesh/MeshResource.h"

#include <TktkDX12Game/_MainManager/DX12GameManager.h>
#include "TktkDX12Game/DXGameResource/Mesh/Skeleton/Skeleton.h"
#include "TktkDX12Game/DXGameResource/Mesh/Motion/Motion.h"
#include "TktkDX12Game/DXGameResource/Mesh/BasicMesh/Mesh/BasicMesh.h"
#include "TktkDX12Game/DXGameResource/Mesh/BasicMesh/Material/BasicMeshMaterial.h"
#include "TktkDX12Game/DXGameResource/Mesh/BasicMesh/Loader/BasicMeshPmdLoader.h"
#include "TktkDX12Game/DXGameResource/Mesh/BasicMesh/Loader/BasicMeshPmxLoader.h"

namespace tktk
{
    MeshResource::MeshResource(const MeshResourceNum& resourceNum, const MeshResourceShaderFilePaths& shaderFilePaths)
    {
        // メッシュ共通で使用する座標変換定数バッファを作る
        DX12GameManager::setSystemHandle(SystemCBufferType::MeshTransform, DX12GameManager::createCBuffer(MeshTransformCbuffer()));
        DX12GameManager::setSystemHandle(SystemCBufferType::MeshShadowMap, DX12GameManager::createCBuffer(MeshShadowMapCBuffer()));

        // 各種リソースクラスを作る
        m_skeleton          = std::make_unique<Skeleton>(resourceNum.skeletonNum);
        m_motion            = std::make_unique<Motion>(resourceNum.motionNum);
        m_basicMesh         = std::make_unique<BasicMesh>(shaderFilePaths.writeShadowMapVsFilePath, resourceNum.basicMeshNum);
        m_basicMeshMaterial = std::make_unique<BasicMeshMaterial>(shaderFilePaths.basicShaderFilePaths, shaderFilePaths.monoColorShaderPsFilePath, resourceNum.basicMeshMaterialNum);
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

    size_t MeshResource::createBasicMesh(const BasicMeshInitParam& initParam)
    {
        return m_basicMesh->craete(initParam);
    }

    size_t MeshResource::copyBasicMesh(size_t originalHandle)
    {
        return m_basicMesh->copy(originalHandle);
    }

    size_t MeshResource::createBasicMeshMaterial(const BasicMeshMaterialInitParam& initParam)
    {
        return m_basicMeshMaterial->create(initParam);
    }

    size_t MeshResource::copyBasicMeshMaterial(size_t originalHandle)
    {
        return m_basicMeshMaterial->copy(originalHandle);
    }

    void MeshResource::setMaterialHandle(size_t meshHandle, size_t materialSlot, size_t materialHandle)
    {
        m_basicMesh->setMaterialHandle(meshHandle, materialSlot, materialHandle);
    }

    void MeshResource::writeBasicMeshShadowMap(size_t handle) const
    {
        m_basicMesh->writeShadowMap(handle);
    }

    void MeshResource::setMaterialData(size_t handle) const
    {
        m_basicMeshMaterial->setMaterialData(handle);
    }

    void MeshResource::addMaterialAppendParam(size_t handle, size_t cbufferHandle, size_t dataSize, void* dataTopPos)
    {
        m_basicMeshMaterial->addAppendParam(handle, cbufferHandle, dataSize, dataTopPos);
    }

    void MeshResource::updateMaterialAppendParam(size_t handle, size_t cbufferHandle, size_t dataSize, const void* dataTopPos)
    {
        m_basicMeshMaterial->updateAppendParam(handle, cbufferHandle, dataSize, dataTopPos);
    }

    void MeshResource::drawBasicMesh(size_t handle, const MeshDrawFuncBaseArgs& baseArgs) const
    {
        m_basicMesh->drawMesh(handle, baseArgs);
    }

    BasicMeshLoadPmdReturnValue MeshResource::loadPmd(const BasicMeshLoadPmdArgs& args)
    {
        return BasicMeshPmdLoader::loadPmd(args);
    }

    BasicMeshLoadPmxReturnValue MeshResource::loadPmx(const BasicMeshLoadPmxArgs& args)
    {
        return BasicMeshPmxLoader::loadPmx(args);
    }
}