#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/DXGameShaderResouse.h"

#include "TktkDX12Game/_MainManager/DX12GameManager.h"
#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/Structs/DXGameShaderResouseInitParam.h"
#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/PostEffect/PostEffectMaterialManager.h"
#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/Line2D/Line2DMaterialManager.h"
#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/Sprite/SpriteMaterialManager.h"
#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/Billboard/BillboardMaterialManager.h"
#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/MeshResouse/MeshResource.h"

#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/Structs/ScreenSizeCBufferData.h"

namespace tktk
{
	DXGameShaderResouse::DXGameShaderResouse(const DXGameShaderResouseInitParam& initParam)
	{
		// ゲーム描画エリアの定数バッファを作る
		DrawGameAreaSizeCBufferData drawGameAreaSizeCBufferData{};
		drawGameAreaSizeCBufferData.drawGameAreaSize = DX12GameManager::getDrawGameAreaSize();
		DX12GameManager::setSystemHandle(SystemCBufferType::DrawGameAreaSize, DX12GameManager::createCBuffer(CopySourceDataCarrier(drawGameAreaSizeCBufferData, 0U)));

		m_postEffectMaterial	= std::make_unique<PostEffectMaterialManager>(initParam.postEffectMatMgrParam);
		m_line2DMaterial		= std::make_unique<Line2DMaterialManager>(initParam.line2DMatMgrParam);
		m_spriteMaterial		= std::make_unique<SpriteMaterialManager>(initParam.spriteMatMgrParam);
		// ※ビルボードのパイプラインステートを作る時にスプライトのルートシグネチャを流用しているため、先に「SpriteMaterial」を作る必要がある
		m_billboardMaterial		= std::make_unique<BillboardMaterialManager>(initParam.billboardMatMgrParam);
		m_meshResource			= std::make_unique<MeshResource>(initParam.meshResParam);
	}

	// デストラクタを非インライン化する
	DXGameShaderResouse::~DXGameShaderResouse() = default;

	size_t DXGameShaderResouse::createPostEffectMaterial(const PostEffectMaterialInitParam& initParam)
	{
		return m_postEffectMaterial->create(initParam);
	}

	void DXGameShaderResouse::drawPostEffect(size_t handle, const PostEffectMaterialDrawFuncArgs& drawFuncArgs) const
	{
		m_postEffectMaterial->drawPostEffect(handle, drawFuncArgs);
	}

	void DXGameShaderResouse::addPostEffectMaterialAppendParam(size_t handle, const PostEffectMaterialAppendParamInitParam& initParam)
	{
		m_postEffectMaterial->addPostEffectMaterialAppendParam(handle, initParam);
	}

	void DXGameShaderResouse::updatePostEffectMaterialAppendParam(size_t handle, const PostEffectMaterialAppendParamUpdateFuncArgs& updateFuncArgs)
	{
		m_postEffectMaterial->updatePostEffectMaterialAppendParam(handle, updateFuncArgs);
	}

	size_t DXGameShaderResouse::createSpriteMaterial(const SpriteMaterialInitParam& initParam)
	{
		return m_spriteMaterial->create(initParam);
	}

	const tktkMath::Vector2& DXGameShaderResouse::getSpriteTextureSize(size_t handle) const
	{
		return m_spriteMaterial->getSpriteTextureSize(handle);
	}

	size_t DXGameShaderResouse::getMaxSpriteInstanceCount(size_t handle) const
	{
		return m_spriteMaterial->getMaxInstanceCount(handle);
	}

	size_t DXGameShaderResouse::getCurSpriteInstanceCount(size_t handle) const
	{
		return m_spriteMaterial->getCurInstanceCount(handle);
	}

	void DXGameShaderResouse::clearSpriteInstanceParam(size_t handle)
	{
		m_spriteMaterial->clearInstanceParam(handle);
	}

	void DXGameShaderResouse::addSpriteInstanceParam(size_t handle, float drawPriority, const TempSpriteMaterialInstanceData& instanceParam)
	{
		m_spriteMaterial->addInstanceParam(handle, drawPriority, instanceParam);
	}

	void DXGameShaderResouse::updateSpriteInstanceParam(size_t handle)
	{
		m_spriteMaterial->updateInstanceParam(handle);
	}

	void DXGameShaderResouse::drawSprite(size_t handle, const SpriteMaterialDrawFuncArgs& drawFuncArgs) const
	{
		m_spriteMaterial->draw(handle, drawFuncArgs);
	}

	size_t DXGameShaderResouse::createLine()
	{
		return m_line2DMaterial->create();
	}

	void DXGameShaderResouse::eraseLine(size_t handle)
	{
		m_line2DMaterial->erase(handle);
	}

	void DXGameShaderResouse::drawLine(size_t handle, const Line2DMaterialDrawFuncArgs& drawFuncArgs)
	{
		m_line2DMaterial->drawLine(handle, drawFuncArgs);
	}

	size_t DXGameShaderResouse::createBillboardMaterial(const BillboardMaterialInitParam& initParam)
	{
		return m_billboardMaterial->create(initParam);
	}

	const tktkMath::Vector2& DXGameShaderResouse::getBillboardTextureSize(size_t handle) const
	{
		return m_billboardMaterial->getBillboardTextureSize(handle);
	}

	void DXGameShaderResouse::clearBillboardInstanceParam(size_t handle)
	{
		m_billboardMaterial->clearInstanceParam(handle);
	}

	void DXGameShaderResouse::addBillboardInstanceParam(size_t handle, const BillboardMaterialInstanceData& instanceParam)
	{
		m_billboardMaterial->addInstanceParam(handle, instanceParam);
	}

	void DXGameShaderResouse::updateBillboardInstanceParam(size_t handle, const tktkMath::Matrix4& viewProjMatrix)
	{
		m_billboardMaterial->updateInstanceParam(handle, viewProjMatrix);
	}

	void DXGameShaderResouse::drawBillboard(size_t handle, const BillboardDrawFuncBaseArgs& drawFuncArgs) const
	{
		m_billboardMaterial->draw(handle, drawFuncArgs);
	}

	void DXGameShaderResouse::createSystemMesh()
	{
		m_meshResource->createSystemMesh();
	}

	size_t DXGameShaderResouse::createMesh(const MeshInitParam& initParam)
	{
		return m_meshResource->createMesh(initParam);
	}

	size_t DXGameShaderResouse::copyMesh(size_t originalHandle)
	{
		return m_meshResource->copyMesh(originalHandle);
	}

	size_t DXGameShaderResouse::createMeshMaterial(const MeshMaterialInitParam& initParam)
	{
		return m_meshResource->createMeshMaterial(initParam);
	}

	size_t DXGameShaderResouse::copyMeshMaterial(size_t originalHandle)
	{
		return m_meshResource->copyMeshMaterial(originalHandle);
	}

	size_t DXGameShaderResouse::makeBoxMesh(size_t albedoMapTextureHandle, const MeshDrawFuncRunnerInitParam& funcRunnerInitParam)
	{
		return m_meshResource->makeBoxMesh(albedoMapTextureHandle, funcRunnerInitParam);
	}

	size_t DXGameShaderResouse::makeSkyBoxMesh(size_t skyBoxTextureHandle, const MeshDrawFuncRunnerInitParam& funcRunnerInitParam)
	{
		return m_meshResource->makeSkyBoxMesh(skyBoxTextureHandle, funcRunnerInitParam);
	}

	MeshLoadPmdReturnValue DXGameShaderResouse::loadPmd(const MeshLoadPmdArgs& args, const MeshDrawFuncRunnerInitParam& funcRunnerInitParam)
	{
		return m_meshResource->loadPmd(args, funcRunnerInitParam);
	}

	MeshLoadPmxReturnValue DXGameShaderResouse::loadPmx(const MeshLoadPmxArgs& args, const MeshDrawFuncRunnerInitParam& funcRunnerInitParam)
	{
		return m_meshResource->loadPmx(args, funcRunnerInitParam);
	}

	void DXGameShaderResouse::setMeshMaterialHandle(size_t meshHandle, size_t materialSlot, size_t materialHandle)
	{
		m_meshResource->setMaterialHandle(meshHandle, materialSlot, materialHandle);
	}

	void DXGameShaderResouse::setMeshMaterialData(size_t handle) const
	{
		m_meshResource->setMaterialData(handle);
	}

	void DXGameShaderResouse::addMeshMaterialAppendParam(size_t handle, const MeshMaterialAppendParamInitParam& initParam)
	{
		m_meshResource->addMaterialAppendParam(handle, initParam);
	}

	void DXGameShaderResouse::updateMeshMaterialAppendParam(size_t handle, const MeshMaterialAppendParamUpdateFuncArgs& updateFuncArgs)
	{
		m_meshResource->updateMaterialAppendParam(handle, updateFuncArgs);
	}

	void DXGameShaderResouse::clearMeshInstanceParam(size_t handle)
	{
		m_meshResource->clearInstanceParam(handle);
	}

	void DXGameShaderResouse::addMeshInstanceVertParam(size_t handle, const CopySourceDataCarrier& instanceParam)
	{
		m_meshResource->addInstanceVertParam(handle, instanceParam);
	}

	void DXGameShaderResouse::addMeshInstanceBoneMatrix(size_t meshHandle, size_t skeletonHandle)
	{
		m_meshResource->addInstanceBoneMatrix(meshHandle, skeletonHandle);
	}

	void DXGameShaderResouse::writeMeshShadowMap(size_t handle) const
	{
		m_meshResource->writeShadowMap(handle);
	}

	void DXGameShaderResouse::writeMeshShadowMapUseBone(size_t handle) const
	{
		m_meshResource->writeShadowMapUseBone(handle);
	}

	void DXGameShaderResouse::drawMesh(size_t handle, const MeshDrawFuncBaseArgs& baseArgs) const
	{
		m_meshResource->draw(handle, baseArgs);
	}

	void DXGameShaderResouse::drawMeshUseBone(size_t handle, const MeshDrawFuncBaseArgs& baseArgs) const
	{
		m_meshResource->drawUseBone(handle, baseArgs);
	}

	size_t DXGameShaderResouse::createSkeleton(const SkeletonInitParam& initParam)
	{
		return m_meshResource->createSkeleton(initParam);
	}

	size_t DXGameShaderResouse::copySkeleton(size_t originalHandle)
	{
		return m_meshResource->copySkeleton(originalHandle);
	}

	size_t DXGameShaderResouse::loadMotion(const std::string& motionFileName)
	{
		return m_meshResource->loadMotion(motionFileName);
	}

	size_t DXGameShaderResouse::getMotionEndFrameNo(size_t handle) const
	{
		return m_meshResource->getMotionEndFrameNo(handle);
	}

	void DXGameShaderResouse::updateMotion(size_t skeletonHandle, size_t curMotionHandle, size_t preMotionHandle, float curFrame, float preFrame, float amount)
	{
		m_meshResource->updateMotion(skeletonHandle, curMotionHandle, preMotionHandle, curFrame, preFrame, amount);
	}
}