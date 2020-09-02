#include "TktkDX12Game/DXGameResource/Mesh/MeshResource.h"

#include <TktkDX12Game/_MainManager/DX12GameManager.h>
#include "TktkDX12Game/DXGameResource/Mesh/Skeleton/Skeleton.h"
#include "TktkDX12Game/DXGameResource/Mesh/Motion/Motion.h"
#include "TktkDX12Game/DXGameResource/Mesh/BasicMesh/Mesh/BasicMesh.h"
#include "TktkDX12Game/DXGameResource/Mesh/BasicMesh/Material/BasicMeshMaterial.h"
#include "TktkDX12Game/DXGameResource/Mesh/BasicMesh/Loader/BasicMeshPmdLoader.h"

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

    unsigned int MeshResource::createSkeleton(const SkeletonInitParam& initParam)
    {
        return m_skeleton->create(initParam);
    }

    unsigned int MeshResource::copySkeleton(unsigned int originalHandle)
    {
        return m_skeleton->copy(originalHandle);
    }

    unsigned int MeshResource::createSkeletonCopyBufferHandle(unsigned int handle) const
    {
        return m_skeleton->createCopyBufferHandle(handle);
    }

    void MeshResource::updateBoneMatrixCbuffer(unsigned int handle, unsigned int copyBufferHandle) const
    {
        m_skeleton->updateBoneMatrixCbuffer(handle, copyBufferHandle);
    }

    void MeshResource::resetBoneMatrixCbuffer() const
    {
        m_skeleton->resetBoneMatrixCbuffer();
    }

    unsigned int MeshResource::loadMotion(const std::string& motionFileName)
    {
        return m_motion->load(motionFileName);
    }

    unsigned int MeshResource::getMotionEndFrameNo(unsigned int handle) const
    {
        return m_motion->getEndFrameNo(handle);
    }

    void MeshResource::updateMotion(unsigned int skeletonHandle, unsigned int curMotionHandle, unsigned int preMotionHandle, unsigned int curFrame, unsigned int preFrame, float amount)
    {
        m_skeleton->transform(skeletonHandle, m_motion->calculateBoneTransformMatrices(curMotionHandle, preMotionHandle, curFrame, preFrame, amount));
    }

    unsigned int MeshResource::createBasicMesh(const BasicMeshInitParam& initParam)
    {
        return m_basicMesh->craete(initParam);
    }

    unsigned int MeshResource::copyBasicMesh(unsigned int originalHandle)
    {
        return m_basicMesh->copy(originalHandle);
    }

    unsigned int MeshResource::createBasicMeshMaterial(const BasicMeshMaterialInitParam& initParam)
    {
        return m_basicMeshMaterial->create(initParam);
    }

    unsigned int MeshResource::copyBasicMeshMaterial(unsigned int originalHandle)
    {
        return m_basicMeshMaterial->copy(originalHandle);
    }

    void MeshResource::setMaterialHandle(unsigned int meshHandle, unsigned int materialSlot, unsigned int materialHandle)
    {
        m_basicMesh->setMaterialHandle(meshHandle, materialSlot, materialHandle);
    }

    void MeshResource::writeBasicMeshShadowMap(unsigned int handle) const
    {
        m_basicMesh->writeShadowMap(handle);
    }

    void MeshResource::setMaterialData(unsigned int handle) const
    {
        m_basicMeshMaterial->setMaterialData(handle);
    }

    void MeshResource::addMaterialAppendParam(unsigned int handle, unsigned int cbufferHandle, unsigned int dataSize, void* dataTopPos)
    {
        m_basicMeshMaterial->addAppendParam(handle, cbufferHandle, dataSize, dataTopPos);
    }

    void MeshResource::updateMaterialAppendParam(unsigned int handle, unsigned int cbufferHandle, unsigned int dataSize, const void* dataTopPos)
    {
        m_basicMeshMaterial->updateAppendParam(handle, cbufferHandle, dataSize, dataTopPos);
    }

    void MeshResource::drawBasicMesh(unsigned int handle, const MeshDrawFuncBaseArgs& baseArgs) const
    {
        m_basicMesh->drawMesh(handle, baseArgs);
    }

    BasicMeshLoadPmdReturnValue MeshResource::loadPmd(const BasicMeshLoadPmdArgs& args)
    {
        return BasicMeshPmdLoader::loadPmd(args);
    }
}