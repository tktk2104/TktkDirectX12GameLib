#include "TktkDX12Game/DXGameResource/DXGameResource.h"

#include "TktkDX12Game/DXGameResource/DXGameResourceInitParam.h"
#include "TktkDX12Game/DXGameResource/Draw3DParameters/Draw3DParameters.h"
#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/DXGameShaderResouse.h"
#include "TktkDX12Game/DXGameResource/GameObjectResouse/GameObjectResouse.h"
#include "TktkDX12Game/DXGameResource/OtherResouse/OtherResouse.h"

#include "TktkDX12Game/_MainManager/DX12GameManager.h"

namespace tktk
{
	DXGameResource::DXGameResource(const DXGameResourceInitParam& initParam)
	{
		// 各種リソースクラスを作る
		m_draw3DParameters		= std::make_unique<Draw3DParameters>(initParam.draw3DParam);
		m_dxGameShaderResouse	= std::make_unique<DXGameShaderResouse>(initParam.dxGameShaderResParam);
		m_gameObjectResouse		= std::make_unique<GameObjectResouse>();
		m_otherResouse			= std::make_unique<OtherResouse>(initParam.otherResParam);
	}

	// デストラクタを非インライン化する
	DXGameResource::~DXGameResource() = default;

	void DXGameResource::update()
	{
		m_otherResouse->update();

		// 前フレームに追加された要素をメインリストに移動する
		m_gameObjectResouse->movePreFrameAddedNode();

		m_gameObjectResouse->update();
	}

	void DXGameResource::removeDeadInstance()
	{
		m_gameObjectResouse->removeDeadInstance();
	}

	void DXGameResource::draw()
	{
		m_gameObjectResouse->draw();
	}

	size_t DXGameResource::createScene(const SceneInitParam& initParam)
	{
		return m_otherResouse->createScene(initParam);
	}

	void DXGameResource::setSceneEndDestroyGameObjectTag(size_t handle, GameObjectTagCarrier tag)
	{
		m_otherResouse->setSceneEndDestroyGameObjectTag(handle, tag);
	}

	void DXGameResource::enableScene(size_t handle)
	{
		m_otherResouse->enableScene(handle);
	}

	void DXGameResource::disableScene(size_t handle)
	{
		m_otherResouse->disableScene(handle);
	}

	void DXGameResource::clearSound()
	{
		m_otherResouse->clearSound();
	}

	size_t DXGameResource::loadSound(const std::string& fileName)
	{
		return m_otherResouse->loadSound(fileName);
	}

	void DXGameResource::playSound(size_t handle, bool loopPlay)
	{
		m_otherResouse->playSound(handle, loopPlay);
	}

	void DXGameResource::stopSound(size_t handle)
	{
		m_otherResouse->stopSound(handle);
	}

	void DXGameResource::pauseSound(size_t handle)
	{
		m_otherResouse->pauseSound(handle);
	}

	void DXGameResource::setMasterVolume(float volume)
	{
		m_otherResouse->setMasterVolume(volume);
	}

	void DXGameResource::runHandleMessageAll(MessageTypeCarrier type, const MessageAttachment& attachment)
	{
		m_gameObjectResouse->runHandleMessageAll(type, attachment);
	}

	GameObjectPtr DXGameResource::createGameObject()
	{
		return m_gameObjectResouse->createGameObject();
	}

	GameObjectPtr DXGameResource::findGameObjectWithTag(GameObjectTagCarrier tag) const
	{
		return m_gameObjectResouse->findGameObjectWithTag(tag);
	}

	std::forward_list<GameObjectPtr> DXGameResource::findGameObjectsWithTag(GameObjectTagCarrier tag) const
	{
		return m_gameObjectResouse->findGameObjectsWithTag(tag);
	}

	void DXGameResource::destroyGameObjectsWithTag(GameObjectTagCarrier tag)
	{
		m_gameObjectResouse->destroyGameObjectsWithTag(tag);
	}

	void DXGameResource::addRunFuncPriority(std::type_index type, float priority)
	{
		m_gameObjectResouse->addRunFuncPriority(type, priority);
	}

	void DXGameResource::addCollisionGroup(CollisionGroupTypeCarrier firstGroup, CollisionGroupTypeCarrier secondGroup)
	{
		m_gameObjectResouse->addCollisionGroup(firstGroup, secondGroup);
	}

	ComponentBasePtr DXGameResource::addComponent(std::type_index type, ComponentVTableBundle* vtablePtrBundle, ComponentListVTable* listVtablePtr, const GameObjectPtr& user, const std::shared_ptr<ComponentBase>& componentPtr)
	{
		return m_gameObjectResouse->addComponent(type, vtablePtrBundle, listVtablePtr, user, componentPtr);
	}

	size_t DXGameResource::createPostEffectMaterial(const PostEffectMaterialInitParam& initParam)
	{
		return m_dxGameShaderResouse->createPostEffectMaterial(initParam);
	}

	void DXGameResource::drawPostEffect(size_t handle, const PostEffectMaterialDrawFuncArgs& drawFuncArgs) const
	{
		m_dxGameShaderResouse->drawPostEffect(handle, drawFuncArgs);
	}

	size_t DXGameResource::createSpriteMaterial(const SpriteMaterialInitParam& initParam)
	{
		return m_dxGameShaderResouse->createSpriteMaterial(initParam);
	}

	void DXGameResource::drawSprite(size_t handle, const SpriteMaterialDrawFuncArgs& drawFuncArgs) const
	{
		m_dxGameShaderResouse->drawSprite(handle, drawFuncArgs);
	}

	void DXGameResource::updateSpriteTransformCbuffer(size_t handle, size_t copyBufferHandle, const SpriteCbufferUpdateFuncArgs& cbufferUpdateArgs) const
	{
		m_dxGameShaderResouse->updateSpriteTransformCbuffer(handle, copyBufferHandle, cbufferUpdateArgs);
	}

	void DXGameResource::updateSpriteTransformCbufferUseClippingParam(size_t handle, size_t copyBufferHandle, const SpriteCbufferUpdateFuncArgs& cbufferUpdateArgs, const SpriteClippingParam& clippingParam) const
	{
		m_dxGameShaderResouse->updateSpriteTransformCbufferUseClippingParam(handle, copyBufferHandle, cbufferUpdateArgs, clippingParam);
	}

	size_t DXGameResource::createLine()
	{
		return m_dxGameShaderResouse->createLine();
	}

	void DXGameResource::eraseLine(size_t handle)
	{
		m_dxGameShaderResouse->eraseLine(handle);
	}

	void DXGameResource::drawLine(size_t handle, const Line2DMaterialDrawFuncArgs& drawFuncArgs)
	{
		m_dxGameShaderResouse->drawLine(handle, drawFuncArgs);
	}

	size_t DXGameResource::createBillboardMaterial(const BillboardMaterialInitParam& initParam)
	{
		return m_dxGameShaderResouse->createBillboardMaterial(initParam);
	}

	void DXGameResource::drawBillboard(size_t handle, const BillboardDrawFuncBaseArgs& drawFuncArgs) const
	{
		m_dxGameShaderResouse->drawBillboard(handle, drawFuncArgs);
	}

	void DXGameResource::updateBillboardCbuffer(size_t handle, size_t copyBufferHandle, const BillboardCbufferUpdateFuncArgs& updateArgs) const
	{
		m_dxGameShaderResouse->updateBillboardCbuffer(handle, copyBufferHandle, updateArgs);
	}

	void DXGameResource::updateBillboardCbufferUseClippingParam(size_t handle, size_t copyBufferHandle, const BillboardCbufferUpdateFuncArgs& updateArgs, const BillboardClippingParam& clippingParam) const
	{
		m_dxGameShaderResouse->updateBillboardCbufferUseClippingParam(handle, copyBufferHandle, updateArgs, clippingParam);
	}

	size_t DXGameResource::createBasicMesh(const MeshInitParam& initParam)
	{
		return m_dxGameShaderResouse->createBasicMesh(initParam);
	}

	size_t DXGameResource::copyBasicMesh(size_t originalHandle)
	{
		return m_dxGameShaderResouse->copyBasicMesh(originalHandle);
	}

	size_t DXGameResource::createBasicMeshMaterial(const MeshMaterialInitParam& initParam)
	{
		return m_dxGameShaderResouse->createBasicMeshMaterial(initParam);
	}

	size_t DXGameResource::copyBasicMeshMaterial(size_t originalHandle)
	{
		return m_dxGameShaderResouse->copyBasicMeshMaterial(originalHandle);
	}

	void DXGameResource::setMaterialHandle(size_t meshHandle, size_t materialSlot, size_t materialHandle)
	{
		m_dxGameShaderResouse->setMaterialHandle(meshHandle, materialSlot, materialHandle);
	}

	void DXGameResource::writeBasicMeshShadowMap(size_t handle) const
	{
		m_dxGameShaderResouse->writeBasicMeshShadowMap(handle);
	}

	void DXGameResource::setMaterialData(size_t handle) const
	{
		m_dxGameShaderResouse->setMaterialData(handle);
	}

	void DXGameResource::addMaterialAppendParam(size_t handle, const MeshMaterialAppendParamInitParam& initParam)
	{
		m_dxGameShaderResouse->addMaterialAppendParam(handle, initParam);
	}

	void DXGameResource::updateMaterialAppendParam(size_t handle, const MeshMaterialAppendParamUpdateFuncArgs& updateFuncArgs)
	{
		m_dxGameShaderResouse->updateMaterialAppendParam(handle, updateFuncArgs);
	}

	void DXGameResource::drawBasicMesh(size_t handle, const MeshDrawFuncBaseArgs& baseArgs) const
	{
		m_dxGameShaderResouse->drawBasicMesh(handle, baseArgs);
	}

	MeshLoadPmdReturnValue DXGameResource::loadPmd(const MeshLoadPmdArgs& args)
	{
		return m_dxGameShaderResouse->loadPmd(args);
	}

	MeshLoadPmxReturnValue DXGameResource::loadPmx(const MeshLoadPmxArgs& args)
	{
		return m_dxGameShaderResouse->loadPmx(args);
	}

	size_t DXGameResource::createSkeleton(const SkeletonInitParam& initParam)
	{
		return m_dxGameShaderResouse->createSkeleton(initParam);
	}

	size_t DXGameResource::copySkeleton(size_t originalHandle)
	{
		return m_dxGameShaderResouse->copySkeleton(originalHandle);
	}

	size_t DXGameResource::createSkeletonUploadBufferHandle(size_t handle) const
	{
		return m_dxGameShaderResouse->createSkeletonUploadBufferHandle(handle);
	}

	void DXGameResource::updateBoneMatrixCbuffer(size_t handle, size_t copyBufferHandle) const
	{
		m_dxGameShaderResouse->updateBoneMatrixCbuffer(handle, copyBufferHandle);
	}

	void DXGameResource::resetBoneMatrixCbuffer() const
	{
		m_dxGameShaderResouse->resetBoneMatrixCbuffer();
	}

	size_t DXGameResource::loadMotion(const std::string& motionFileName)
	{
		return m_dxGameShaderResouse->loadMotion(motionFileName);
	}

	size_t DXGameResource::getMotionEndFrameNo(size_t handle) const
	{
		return m_dxGameShaderResouse->getMotionEndFrameNo(handle);
	}

	void DXGameResource::updateMotion(size_t skeletonHandle, size_t curMotionHandle, size_t preMotionHandle, size_t curFrame, size_t preFrame, float amount)
	{
		m_dxGameShaderResouse->updateMotion(skeletonHandle, curMotionHandle, preMotionHandle, curFrame, preFrame, amount);
	}

	size_t DXGameResource::createCamera()
	{
		return m_draw3DParameters->createCamera();
	}

	const tktkMath::Matrix4& DXGameResource::getViewMatrix(size_t cameraHandle) const
	{
		return m_draw3DParameters->getViewMatrix(cameraHandle);
	}

	void DXGameResource::setViewMatrix(size_t cameraHandle, const tktkMath::Matrix4& view)
	{
		m_draw3DParameters->setViewMatrix(cameraHandle, view);
	}

	const tktkMath::Matrix4& DXGameResource::getProjectionMatrix(size_t cameraHandle) const
	{
		return m_draw3DParameters->getProjectionMatrix(cameraHandle);
	}

	void DXGameResource::setProjectionMatrix(size_t cameraHandle, const tktkMath::Matrix4& projection)
	{
		m_draw3DParameters->setProjectionMatrix(cameraHandle, projection);
	}

	size_t DXGameResource::createLight(const tktkMath::Color& ambient, const tktkMath::Color& diffuse, const tktkMath::Color& speqular, const tktkMath::Vector3& position)
	{
	 	return m_draw3DParameters->createLight(ambient, diffuse, speqular, position);
	}

	void DXGameResource::updateLightCBuffer(size_t handle) const
	{
		m_draw3DParameters->updateLightCBuffer(handle);
	}

	void DXGameResource::setLightAmbient(size_t handle, const tktkMath::Color& ambient)
	{
		return m_draw3DParameters->setLightAmbient(handle, ambient);
	}

	void DXGameResource::setLightDiffuse(size_t handle, const tktkMath::Color& diffuse)
	{
		return m_draw3DParameters->setLightDiffuse(handle, diffuse);
	}

	void DXGameResource::setLightSpeqular(size_t handle, const tktkMath::Color& speqular)
	{
		return m_draw3DParameters->setLightSpeqular(handle, speqular);
	}

	void DXGameResource::setLightPosition(size_t handle, const tktkMath::Vector3& position)
	{
		return m_draw3DParameters->setLightPosition(handle, position);
	}
}