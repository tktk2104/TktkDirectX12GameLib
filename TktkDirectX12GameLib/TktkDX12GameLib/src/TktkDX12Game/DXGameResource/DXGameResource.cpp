#include "TktkDX12Game/DXGameResource/DXGameResource.h"

#include "TktkDX12Game/_MainManager/DX12GameManager.h"
#include "TktkDX12Game/DXGameResource/Scene/SceneManager.h"
#include "TktkDX12Game/DXGameResource/Sound/Sound.h"
#include "TktkDX12Game/DXGameResource/PostEffect/PostEffectMaterial.h"
#include "TktkDX12Game/DXGameResource/Sprite/SpriteMaterial.h"
#include "TktkDX12Game/DXGameResource/Line2D/Line2DMaterial.h"
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
		m_meshResource			= std::make_unique<MeshResource>(resourceNum.meshResourceNum, filePaths.meshResourceShaderFilePaths);
		m_camera				= std::make_unique<Camera>(resourceNum.cameraNum);
		m_light					= std::make_unique<Light>(resourceNum.lightNum);
	}

	// デストラクタを非インライン化する
	DXGameResource::~DXGameResource() = default;

	unsigned int DXGameResource::createScene(const std::shared_ptr<SceneBase>& scenePtr, SceneVTable* vtablePtr)
	{
		return m_sceneManager->create(scenePtr, vtablePtr);
	}

	void DXGameResource::enableScene(unsigned int handle)
	{
		m_sceneManager->enable(handle);
	}

	void DXGameResource::disableScene(unsigned int handle)
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

	unsigned int DXGameResource::loadSound(const std::string& fileName)
	{
		return m_sound->load(fileName);
	}

	void DXGameResource::playSound(unsigned int handle, bool loopPlay)
	{
		m_sound->play(handle, loopPlay);
	}

	void DXGameResource::stopSound(unsigned int handle)
	{
		m_sound->stop(handle);
	}

	void DXGameResource::pauseSound(unsigned int handle)
	{
		m_sound->pause(handle);
	}

	void DXGameResource::setMasterVolume(float volume)
	{
		m_sound->setMasterVolume(volume);
	}

	unsigned int DXGameResource::createPostEffectMaterial(const PostEffectMaterialInitParam& initParam)
	{
		return m_postEffectMaterial->create(initParam);
	}

	void DXGameResource::drawPostEffect(unsigned int handle, const PostEffectMaterialDrawFuncArgs& drawFuncArgs) const
	{
		m_postEffectMaterial->drawPostEffect(handle, drawFuncArgs);
	}

	unsigned int DXGameResource::createSpriteMaterial(const SpriteMaterialInitParam& initParam)
	{
		return m_spriteMaterial->create(initParam);
	}

	void DXGameResource::drawSprite(unsigned int handle, const SpriteMaterialDrawFuncArgs& drawFuncArgs) const
	{
		m_spriteMaterial->drawSprite(handle, drawFuncArgs);
	}

	void DXGameResource::updateSpriteTransformCbuffer(unsigned int handle, unsigned int copyBufferHandle, const tktkMath::Matrix3& worldMatrix, const tktkMath::Vector2& spriteCenterRate) const
	{
		m_spriteMaterial->updateTransformCbuffer(handle, copyBufferHandle, worldMatrix, spriteCenterRate);
	}

	void DXGameResource::updateSpriteTransformCbufferUseClippingParam(unsigned int handle, unsigned int copyBufferHandle, const tktkMath::Matrix3& worldMatrix, const tktkMath::Vector2& spriteCenterRate, const SpriteClippingParam& clippingParam) const
	{
		m_spriteMaterial->updateTransformCbufferUseClippingParam(handle, copyBufferHandle, worldMatrix, spriteCenterRate, clippingParam);
	}

	unsigned int DXGameResource::createLine()
	{
		return m_line2DMaterial->create();
	}

	void DXGameResource::drawLine(unsigned int handle, const Line2DMaterialDrawFuncArgs& drawFuncArgs)
	{
		m_line2DMaterial->drawLine(handle, drawFuncArgs);
	}

	unsigned int DXGameResource::createBasicMesh(const BasicMeshInitParam& initParam)
	{
		return m_meshResource->createBasicMesh(initParam);
	}

	unsigned int DXGameResource::copyBasicMesh(unsigned int originalHandle)
	{
		return m_meshResource->copyBasicMesh(originalHandle);
	}

	unsigned int DXGameResource::createBasicMeshMaterial(const BasicMeshMaterialInitParam& initParam)
	{
		return m_meshResource->createBasicMeshMaterial(initParam);
	}

	unsigned int DXGameResource::copyBasicMeshMaterial(unsigned int originalHandle)
	{
		return m_meshResource->copyBasicMeshMaterial(originalHandle);
	}

	void DXGameResource::setMaterialHandle(unsigned int meshHandle, unsigned int materialSlot, unsigned int materialHandle)
	{
		m_meshResource->setMaterialHandle(meshHandle, materialSlot, materialHandle);
	}

	void DXGameResource::writeBasicMeshShadowMap(unsigned int handle) const
	{
		m_meshResource->writeBasicMeshShadowMap(handle);
	}

	void DXGameResource::setMaterialData(unsigned int handle) const
	{
		m_meshResource->setMaterialData(handle);
	}

	void DXGameResource::addMaterialAppendParam(unsigned int handle, unsigned int cbufferHandle, unsigned int dataSize, void* dataTopPos)
	{
		m_meshResource->addMaterialAppendParam(handle, cbufferHandle, dataSize, dataTopPos);
	}

	void DXGameResource::updateMaterialAppendParam(unsigned int handle, unsigned int cbufferHandle, unsigned int dataSize, const void* dataTopPos)
	{
		m_meshResource->updateMaterialAppendParam(handle, cbufferHandle, dataSize, dataTopPos);
	}

	void DXGameResource::drawBasicMesh(unsigned int handle, const MeshDrawFuncBaseArgs& baseArgs) const
	{
		m_meshResource->drawBasicMesh(handle, baseArgs);
	}

	BasicMeshLoadPmdReturnValue DXGameResource::loadPmd(const BasicMeshLoadPmdArgs& args)
	{
		return m_meshResource->loadPmd(args);
	}

	unsigned int DXGameResource::createSkeleton(const SkeletonInitParam& initParam)
	{
		return m_meshResource->createSkeleton(initParam);
	}

	unsigned int DXGameResource::copySkeleton(unsigned int originalHandle)
	{
		return m_meshResource->copySkeleton(originalHandle);
	}

	unsigned int DXGameResource::createSkeletonCopyBufferHandle(unsigned int handle) const
	{
		return m_meshResource->createSkeletonCopyBufferHandle(handle);
	}

	void DXGameResource::updateBoneMatrixCbuffer(unsigned int handle, unsigned int copyBufferHandle) const
	{
		m_meshResource->updateBoneMatrixCbuffer(handle, copyBufferHandle);
	}

	void DXGameResource::resetBoneMatrixCbuffer() const
	{
		m_meshResource->resetBoneMatrixCbuffer();
	}

	unsigned int DXGameResource::loadMotion(const std::string& motionFileName)
	{
		return m_meshResource->loadMotion(motionFileName);
	}

	unsigned int DXGameResource::getMotionEndFrameNo(unsigned int handle) const
	{
		return m_meshResource->getMotionEndFrameNo(handle);
	}

	void DXGameResource::updateMotion(unsigned int skeletonHandle, unsigned int curMotionHandle, unsigned int preMotionHandle, unsigned int curFrame, unsigned int preFrame, float amount)
	{
		m_meshResource->updateMotion(skeletonHandle, curMotionHandle, preMotionHandle, curFrame, preFrame, amount);
	}

	unsigned int DXGameResource::createCamera()
	{
		return m_camera->create();
	}

	const tktkMath::Matrix4& DXGameResource::getViewMatrix(unsigned int cameraHandle) const
	{
		return m_camera->getViewMatrix(cameraHandle);
	}

	void DXGameResource::setViewMatrix(unsigned int cameraHandle, const tktkMath::Matrix4& view)
	{
		m_camera->setViewMatrix(cameraHandle, view);
	}

	const tktkMath::Matrix4& DXGameResource::getProjectionMatrix(unsigned int cameraHandle) const
	{
		return m_camera->getProjectionMatrix(cameraHandle);
	}

	void DXGameResource::setProjectionMatrix(unsigned int cameraHandle, const tktkMath::Matrix4& projection)
	{
		m_camera->setProjectionMatrix(cameraHandle, projection);
	}

	unsigned int DXGameResource::createLight(const tktkMath::Color& ambient, const tktkMath::Color& diffuse, const tktkMath::Color& speqular, const tktkMath::Vector3& position)
	{
	 	return m_light->create(ambient, diffuse, speqular, position);
	}

	void DXGameResource::updateLightCBuffer(unsigned int handle) const
	{
		m_light->updateLightCBuffer(handle);
	}

	void DXGameResource::setLightAmbient(unsigned int handle, const tktkMath::Color& ambient)
	{
		return m_light->setAmbient(handle, ambient);
	}

	void DXGameResource::setLightDiffuse(unsigned int handle, const tktkMath::Color& diffuse)
	{
		return m_light->setDiffuse(handle, diffuse);
	}

	void DXGameResource::setLightSpeqular(unsigned int handle, const tktkMath::Color& speqular)
	{
		return m_light->setSpeqular(handle, speqular);
	}

	void DXGameResource::setLightPosition(unsigned int handle, const tktkMath::Vector3& position)
	{
		return m_light->setPosition(handle, position);
	}
}