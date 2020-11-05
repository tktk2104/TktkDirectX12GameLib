#include "TktkDX12Game/DXGameResource/DXGameResource.h"

#include "TktkDX12Game/_MainManager/DX12GameManager.h"
#include "TktkDX12Game/DXGameResource/Scene/SceneManager.h"
#include "TktkDX12Game/DXGameResource/Sound/Sound.h"
#include "TktkDX12Game/DXGameResource/PostEffect/PostEffectMaterial.h"
#include "TktkDX12Game/DXGameResource/Sprite/SpriteMaterial.h"
#include "TktkDX12Game/DXGameResource/Line2D/Line2DMaterial.h"
#include "TktkDX12Game/DXGameResource/Billboard/BillboardMaterial.h"
#include "TktkDX12Game/DXGameResource/Mesh/MeshResource.h"
#include "TktkDX12Game/DXGameResource/Camera/Camera.h"
#include "TktkDX12Game/DXGameResource/Light/Light.h"

namespace tktk
{
	DXGameResource::DXGameResource(const DXGameResourceNum& resourceNum, const DXGameBaseShaderFilePaths& filePaths)
	{
		// 各種リソースクラスを作る
		m_sceneManager			= std::make_unique<SceneManager>(resourceNum.sceneNum);
		m_sound					= std::make_unique<Sound>(resourceNum.soundNum);
		m_postEffectMaterial	= std::make_unique<PostEffectMaterial>(filePaths.postEffectShaderFilePaths, resourceNum.postEffectMaterialNum);
		m_spriteMaterial		= std::make_unique<SpriteMaterial>(filePaths.spriteShaderFilePaths, resourceNum.spriteMaterialNum);
		m_line2DMaterial		= std::make_unique<Line2DMaterial>(filePaths.line2DShaderFilePaths, resourceNum.line2DMaterialNum);
		
		// ※ビルボードのパイプラインステートを作る時にスプライトのルートシグネチャを流用しているため、先に「SpriteMaterial」を作る必要がある
		m_billboardMaterial		= std::make_unique<BillboardMaterial>(filePaths.billboardShaderFilePaths, resourceNum.billboardMaterialNum);
		m_meshResource			= std::make_unique<MeshResource>(resourceNum.meshResourceNum, filePaths.meshResourceShaderFilePaths);
		m_camera				= std::make_unique<Camera>(resourceNum.cameraNum);
		m_light					= std::make_unique<Light>(resourceNum.lightNum);
	}

	// デストラクタを非インライン化する
	DXGameResource::~DXGameResource() = default;

	size_t DXGameResource::createScene(const SceneDataInitParam& initParam)
	{
		return m_sceneManager->create(initParam);
	}

	void DXGameResource::setSceneEndDestroyGameObjectTag(size_t handle, GameObjectTagCarrier tag)
	{
		m_sceneManager->setSceneEndDestroyGameObjectTag(handle, tag);
	}

	void DXGameResource::enableScene(size_t handle)
	{
		m_sceneManager->enable(handle);
	}

	void DXGameResource::disableScene(size_t handle)
	{
		m_sceneManager->disable(handle);
	}

	void DXGameResource::updateScene()
	{
		m_sceneManager->update();
	}

	void DXGameResource::updateSound()
	{
		m_sound->update();
	}

	void DXGameResource::clearSound()
	{
		m_sound->clear();
	}

	size_t DXGameResource::loadSound(const std::string& fileName)
	{
		return m_sound->load(fileName);
	}

	void DXGameResource::playSound(size_t handle, bool loopPlay)
	{
		m_sound->play(handle, loopPlay);
	}

	void DXGameResource::stopSound(size_t handle)
	{
		m_sound->stop(handle);
	}

	void DXGameResource::pauseSound(size_t handle)
	{
		m_sound->pause(handle);
	}

	void DXGameResource::setMasterVolume(float volume)
	{
		m_sound->setMasterVolume(volume);
	}

	size_t DXGameResource::createPostEffectMaterial(const PostEffectMaterialInitParam& initParam)
	{
		return m_postEffectMaterial->create(initParam);
	}

	void DXGameResource::drawPostEffect(size_t handle, const PostEffectMaterialDrawFuncArgs& drawFuncArgs) const
	{
		m_postEffectMaterial->drawPostEffect(handle, drawFuncArgs);
	}

	size_t DXGameResource::createSpriteMaterial(const SpriteMaterialInitParam& initParam)
	{
		return m_spriteMaterial->create(initParam);
	}

	void DXGameResource::drawSprite(size_t handle, const SpriteMaterialDrawFuncArgs& drawFuncArgs) const
	{
		m_spriteMaterial->drawSprite(handle, drawFuncArgs);
	}

	void DXGameResource::updateSpriteTransformCbuffer(size_t handle, size_t copyBufferHandle, const tktkMath::Matrix3& worldMatrix, const tktkMath::Vector2& spriteCenterRate) const
	{
		m_spriteMaterial->updateTransformCbuffer(handle, copyBufferHandle, worldMatrix, spriteCenterRate);
	}

	void DXGameResource::updateSpriteTransformCbufferUseClippingParam(size_t handle, size_t copyBufferHandle, const tktkMath::Matrix3& worldMatrix, const tktkMath::Vector2& spriteCenterRate, const SpriteClippingParam& clippingParam) const
	{
		m_spriteMaterial->updateTransformCbufferUseClippingParam(handle, copyBufferHandle, worldMatrix, spriteCenterRate, clippingParam);
	}

	size_t DXGameResource::createLine()
	{
		return m_line2DMaterial->create();
	}

	void DXGameResource::eraseLine(size_t handle)
	{
		m_line2DMaterial->erase(handle);
	}

	void DXGameResource::drawLine(size_t handle, const Line2DMaterialDrawFuncArgs& drawFuncArgs)
	{
		m_line2DMaterial->drawLine(handle, drawFuncArgs);
	}

	size_t DXGameResource::createBillboardMaterial(const BillboardMaterialInitParam& initParam)
	{
		return m_billboardMaterial->create(initParam);
	}

	void DXGameResource::drawBillboard(size_t handle, const BillboardDrawFuncBaseArgs& drawFuncArgs) const
	{
		m_billboardMaterial->drawBillboard(handle, drawFuncArgs);
	}

	void DXGameResource::updateBillboardCbuffer(size_t handle, size_t copyBufferHandle, const BillboardCbufferUpdateFuncArgs& updateArgs) const
	{
		m_billboardMaterial->updateTransformCbuffer(handle, copyBufferHandle, updateArgs);
	}

	void DXGameResource::updateBillboardCbufferUseClippingParam(size_t handle, size_t copyBufferHandle, const BillboardCbufferUpdateFuncArgs& updateArgs, const BillboardClippingParam& clippingParam) const
	{
		m_billboardMaterial->updateTransformCbufferUseClippingParam(handle, copyBufferHandle, updateArgs, clippingParam);
	}

	size_t DXGameResource::createBasicMesh(const BasicMeshInitParam& initParam)
	{
		return m_meshResource->createBasicMesh(initParam);
	}

	size_t DXGameResource::copyBasicMesh(size_t originalHandle)
	{
		return m_meshResource->copyBasicMesh(originalHandle);
	}

	size_t DXGameResource::createBasicMeshMaterial(const BasicMeshMaterialInitParam& initParam)
	{
		return m_meshResource->createBasicMeshMaterial(initParam);
	}

	size_t DXGameResource::copyBasicMeshMaterial(size_t originalHandle)
	{
		return m_meshResource->copyBasicMeshMaterial(originalHandle);
	}

	void DXGameResource::setMaterialHandle(size_t meshHandle, size_t materialSlot, size_t materialHandle)
	{
		m_meshResource->setMaterialHandle(meshHandle, materialSlot, materialHandle);
	}

	void DXGameResource::writeBasicMeshShadowMap(size_t handle) const
	{
		m_meshResource->writeBasicMeshShadowMap(handle);
	}

	void DXGameResource::setMaterialData(size_t handle) const
	{
		m_meshResource->setMaterialData(handle);
	}

	void DXGameResource::addMaterialAppendParam(size_t handle, size_t cbufferHandle, size_t dataSize, void* dataTopPos)
	{
		m_meshResource->addMaterialAppendParam(handle, cbufferHandle, dataSize, dataTopPos);
	}

	void DXGameResource::updateMaterialAppendParam(size_t handle, size_t cbufferHandle, size_t dataSize, const void* dataTopPos)
	{
		m_meshResource->updateMaterialAppendParam(handle, cbufferHandle, dataSize, dataTopPos);
	}

	void DXGameResource::drawBasicMesh(size_t handle, const MeshDrawFuncBaseArgs& baseArgs) const
	{
		m_meshResource->drawBasicMesh(handle, baseArgs);
	}

	BasicMeshLoadPmdReturnValue DXGameResource::loadPmd(const BasicMeshLoadPmdArgs& args)
	{
		return m_meshResource->loadPmd(args);
	}

	BasicMeshLoadPmxReturnValue DXGameResource::loadPmx(const BasicMeshLoadPmxArgs& args)
	{
		return m_meshResource->loadPmx(args);
	}

	size_t DXGameResource::createSkeleton(const SkeletonInitParam& initParam)
	{
		return m_meshResource->createSkeleton(initParam);
	}

	size_t DXGameResource::copySkeleton(size_t originalHandle)
	{
		return m_meshResource->copySkeleton(originalHandle);
	}

	size_t DXGameResource::createSkeletonUploadBufferHandle(size_t handle) const
	{
		return m_meshResource->createSkeletonUploadBufferHandle(handle);
	}

	void DXGameResource::updateBoneMatrixCbuffer(size_t handle, size_t copyBufferHandle) const
	{
		m_meshResource->updateBoneMatrixCbuffer(handle, copyBufferHandle);
	}

	void DXGameResource::resetBoneMatrixCbuffer() const
	{
		m_meshResource->resetBoneMatrixCbuffer();
	}

	size_t DXGameResource::loadMotion(const std::string& motionFileName)
	{
		return m_meshResource->loadMotion(motionFileName);
	}

	size_t DXGameResource::getMotionEndFrameNo(size_t handle) const
	{
		return m_meshResource->getMotionEndFrameNo(handle);
	}

	void DXGameResource::updateMotion(size_t skeletonHandle, size_t curMotionHandle, size_t preMotionHandle, size_t curFrame, size_t preFrame, float amount)
	{
		m_meshResource->updateMotion(skeletonHandle, curMotionHandle, preMotionHandle, curFrame, preFrame, amount);
	}

	size_t DXGameResource::createCamera()
	{
		return m_camera->create();
	}

	const tktkMath::Matrix4& DXGameResource::getViewMatrix(size_t cameraHandle) const
	{
		return m_camera->getViewMatrix(cameraHandle);
	}

	void DXGameResource::setViewMatrix(size_t cameraHandle, const tktkMath::Matrix4& view)
	{
		m_camera->setViewMatrix(cameraHandle, view);
	}

	const tktkMath::Matrix4& DXGameResource::getProjectionMatrix(size_t cameraHandle) const
	{
		return m_camera->getProjectionMatrix(cameraHandle);
	}

	void DXGameResource::setProjectionMatrix(size_t cameraHandle, const tktkMath::Matrix4& projection)
	{
		m_camera->setProjectionMatrix(cameraHandle, projection);
	}

	size_t DXGameResource::createLight(const tktkMath::Color& ambient, const tktkMath::Color& diffuse, const tktkMath::Color& speqular, const tktkMath::Vector3& position)
	{
	 	return m_light->create(ambient, diffuse, speqular, position);
	}

	void DXGameResource::updateLightCBuffer(size_t handle) const
	{
		m_light->updateLightCBuffer(handle);
	}

	void DXGameResource::setLightAmbient(size_t handle, const tktkMath::Color& ambient)
	{
		return m_light->setAmbient(handle, ambient);
	}

	void DXGameResource::setLightDiffuse(size_t handle, const tktkMath::Color& diffuse)
	{
		return m_light->setDiffuse(handle, diffuse);
	}

	void DXGameResource::setLightSpeqular(size_t handle, const tktkMath::Color& speqular)
	{
		return m_light->setSpeqular(handle, speqular);
	}

	void DXGameResource::setLightPosition(size_t handle, const tktkMath::Vector3& position)
	{
		return m_light->setPosition(handle, position);
	}
}