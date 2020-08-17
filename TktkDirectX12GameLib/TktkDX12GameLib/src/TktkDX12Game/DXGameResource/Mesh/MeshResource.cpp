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
        tktk::DX12GameManager::createCBuffer(tktk::DX12GameManager::getSystemId(tktk::SystemCBufferType::MeshTransform), MeshTransformCbuffer());
        tktk::DX12GameManager::createCBuffer(tktk::DX12GameManager::getSystemId(tktk::SystemCBufferType::MeshShadowMap), MeshShadowMapCBuffer());

        // 各種リソースクラスを作る
        m_skeleton          = std::make_unique<Skeleton>(resourceNum.skeletonNum);
        m_motion            = std::make_unique<Motion>(resourceNum.motionNum);
        m_basicMesh         = std::make_unique<BasicMesh>(shaderFilePaths.writeShadowMapVsFilePath, resourceNum.basicMeshNum);
        m_basicMeshMaterial = std::make_unique<BasicMeshMaterial>(shaderFilePaths.basicShaderFilePaths, shaderFilePaths.monoColorShaderPsFilePath, resourceNum.basicMeshMaterialNum);
    }

    // デストラクタを非インライン化する
    MeshResource::~MeshResource() = default;

    void MeshResource::createSkeleton(unsigned int id, const SkeletonInitParam& initParam)
    {
        m_skeleton->create(id, initParam);
    }

    void MeshResource::updateBoneMatrixCbuffer(unsigned int id) const
    {
        m_skeleton->updateBoneMatrixCbuffer(id);
    }

    void MeshResource::resetBoneMatrixCbuffer() const
    {
        m_skeleton->resetBoneMatrixCbuffer();
    }

    void MeshResource::loadMotion(unsigned int id, const std::string& motionFileName)
    {
        m_motion->load(id, motionFileName);
    }

    unsigned int MeshResource::getMotionEndFrameNo(unsigned int id) const
    {
        return m_motion->getEndFrameNo(id);
    }

    void MeshResource::updateMotion(unsigned int skeletonId, unsigned int curMotionId, unsigned int preMotionId, unsigned int curFrame, unsigned int preFrame, float amount)
    {
        m_skeleton->transform(skeletonId, m_motion->calculateBoneTransformMatrices(curMotionId, preMotionId, curFrame, preFrame, amount));
    }

    void MeshResource::createBasicMesh(unsigned int id, const BasicMeshInitParam& initParam)
    {
        m_basicMesh->craete(id, initParam);
    }

    void MeshResource::copyBasicMesh(unsigned int id, unsigned int originalId)
    {
        m_basicMesh->copy(id, originalId);
    }

    void MeshResource::createBasicMeshMaterial(unsigned int id, const BasicMeshMaterialInitParam& initParam)
    {
        m_basicMeshMaterial->create(id, initParam);
    }

    void MeshResource::copyBasicMeshMaterial(unsigned int id, unsigned int originalId)
    {
        m_basicMeshMaterial->copy(id, originalId);
    }

    void MeshResource::setMaterialId(unsigned int id, unsigned int materialSlot, unsigned int materialId)
    {
        m_basicMesh->setMaterialId(id, materialSlot, materialId);
    }

    void MeshResource::writeBasicMeshShadowMap(unsigned int id, const MeshTransformCbuffer& transformBufferData) const
    {
        m_basicMesh->writeShadowMap(id, transformBufferData);
    }

    void MeshResource::setMaterialData(unsigned int id) const
    {
        m_basicMeshMaterial->setMaterialData(id);
    }

    void MeshResource::addMaterialAppendParam(unsigned int id, unsigned int cbufferId, unsigned int dataSize, void* dataTopPos)
    {
        m_basicMeshMaterial->addAppendParam(id, cbufferId, dataSize, dataTopPos);
    }

    void MeshResource::updateMaterialAppendParam(unsigned int id, unsigned int cbufferId, unsigned int dataSize, const void* dataTopPos)
    {
        m_basicMeshMaterial->updateAppendParam(id, cbufferId, dataSize, dataTopPos);
    }

    void MeshResource::drawBasicMesh(unsigned int id, const MeshDrawFuncBaseArgs& baseArgs) const
    {
        m_basicMesh->drawMesh(id, baseArgs);
    }

    BasicMeshLoadPmdReturnValue MeshResource::loadPmd(const BasicMeshLoadPmdArgs& args)
    {
        return BasicMeshPmdLoader::loadPmd(args);
    }
}