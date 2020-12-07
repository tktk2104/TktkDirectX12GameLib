#include "TktkDX12Game/TktkDX12Game.h"

#include <TktkFileIo/FileExtensionGetter.h>
#include "TktkDX12Game/_MainManager/DX12GameManager.h"

namespace tktk
{
	const tktkMath::Vector2& DX12Game::getDrawGameAreaSize()
	{
		return DX12GameManager::getDrawGameAreaSize();
	}

	const tktkMath::Vector2& DX12Game::getScreenSize()
	{
		return DX12GameManager::getScreenSize();
	}

	void DX12Game::enableScene(ResourceIdCarrier id)
	{
		DX12GameManager::enableScene(DX12GameManager::getSceneHandle(id));
	}

	void DX12Game::disableScene(ResourceIdCarrier id)
	{
		DX12GameManager::disableScene(DX12GameManager::getSceneHandle(id));
	}

	void DX12Game::sendMessageAll(MessageTypeCarrier type, const MessageAttachment& attachment)
	{
		DX12GameManager::sendMessageAll(type, attachment);
	}

	GameObjectPtr DX12Game::createGameObject()
	{
		return DX12GameManager::createGameObject();
	}

	GameObjectPtr DX12Game::findGameObjectWithTag(GameObjectTagCarrier tag)
	{
		return DX12GameManager::findGameObjectWithTag(tag);
	}

	std::forward_list<GameObjectPtr> DX12Game::findGameObjectsWithTag(GameObjectTagCarrier tag)
	{
		return DX12GameManager::findGameObjectsWithTag(tag);
	}

	void DX12Game::destroyGameObjectsWithTag(GameObjectTagCarrier tag)
	{
		DX12GameManager::destroyGameObjectsWithTag(tag);
	}

	bool DX12Game::isPush(CommandIdCarrier commandId)
	{
		return DX12GameManager::isPush(commandId);
	}

	bool DX12Game::isTrigger(CommandIdCarrier commandId)
	{
		return DX12GameManager::isTrigger(commandId);
	}

	bool DX12Game::isPush(MouseBtnType btnType)
	{
		return DX12GameManager::isPush(btnType);
	}

	bool DX12Game::isTrigger(MouseBtnType btnType)
	{
		return DX12GameManager::isTrigger(btnType);
	}

	bool DX12Game::isPush(KeybordKeyType keyType)
	{
		return DX12GameManager::isPush(keyType);
	}

	bool DX12Game::isTrigger(KeybordKeyType keyType)
	{
		return DX12GameManager::isTrigger(keyType);
	}

	bool DX12Game::isPush(GamePadBtnType btnType)
	{
		return DX12GameManager::isPush(btnType);
	}

	bool DX12Game::isTrigger(GamePadBtnType btnType)
	{
		return DX12GameManager::isTrigger(btnType);
	}

	const tktkMath::Vector2& DX12Game::moveVec()
	{
		return DX12GameManager::moveVec();
	}

	const tktkMath::Vector2& DX12Game::lookVec()
	{
		return DX12GameManager::lookVec();
	}

	tktkMath::Vector2 DX12Game::mousePos()
	{
		return DX12GameManager::mousePos();
	}

	void DX12Game::resetElapsedTime()
	{
		DX12GameManager::resetElapsedTime();
	}

	float DX12Game::deltaTime()
	{
		return DX12GameManager::deltaTime();
	}

	float DX12Game::noScaleDeltaTime()
	{
		return DX12GameManager::noScaleDeltaTime();
	}

	float DX12Game::getCurTimeSec()
	{
		return DX12GameManager::getCurTimeSec();
	}

	void DX12Game::setMaximumDeltaTime(float maximumDeltaTime)
	{
		DX12GameManager::setMaximumDeltaTime(maximumDeltaTime);
	}

	float DX12Game::getTimeScale()
	{
		return DX12GameManager::getTimeScale();
	}

	void DX12Game::setTimeScale(float timeScaleRate)
	{
		DX12GameManager::setTimeScale(timeScaleRate);
	}

	void DX12Game::setBaseFps(unsigned int baseFps)
	{
		DX12GameManager::setBaseFps(baseFps);
	}

	unsigned int DX12Game::getBaseFps()
	{
		return DX12GameManager::getBaseFps();
	}

	float DX12Game::fps()
	{
		return DX12GameManager::fps();
	}

	void DX12Game::loadSound(ResourceIdCarrier soundId, const std::string& filePath)
	{
		DX12GameManager::loadSoundAndAttachId(soundId, filePath);
	}

	void DX12Game::loadSprite(ResourceIdCarrier spriteId, const std::string& filePath)
	{
		tktk::SpriteMaterialInitParam initParam{};
		initParam.srvBufferType		= tktk::BufferType::texture;
		initParam.useBufferHandle	= tktk::DX12GameManager::cpuPriorityLoadTextureBuffer(filePath);

		tktk::DX12GameManager::createSpriteMaterialAndAttachId(spriteId, initParam);
	}

	void DX12Game::loadBillboard(ResourceIdCarrier billBoardId, bool isEffect, const std::string& filePath)
	{
		tktk::BillboardMaterialInitParam initParam{};
		initParam.srvBufferType		= tktk::BufferType::texture;
		initParam.useBufferHandle	= tktk::DX12GameManager::cpuPriorityLoadTextureBuffer(filePath);
		initParam.maxInstanceCount	= 256U;
		initParam.isEffect			= isEffect;

		tktk::DX12GameManager::createBillboardMaterialAndAttachId(billBoardId, initParam, tktk::BillboardDrawFuncRunnerInitParam::create());
	}

	void DX12Game::loadMesh(ResourceIdCarrier meshId, ResourceIdCarrier skeletonId, bool writeShadow, const std::string& filePath)
	{
		auto extension = tktkFileIo::FileExtensionGetter::get(filePath);

		if (extension == "pmx")
		{
			tktk::MeshLoadPmxArgs loadArgs{};
			loadArgs.filePath			= filePath;
			loadArgs.createBasicMeshId	= meshId;
			loadArgs.createSkeletonId	= skeletonId;

			tktk::DX12GameManager::loadPmx(loadArgs, tktk::MeshDrawFuncRunnerInitParam::create().useBone(true).writeShadowMap(writeShadow));
		}
		else if (extension == "pmd")
		{
			tktk::MeshLoadPmdArgs loadArgs{};
			loadArgs.filePath			= filePath;
			loadArgs.createBasicMeshId	= meshId;
			loadArgs.createSkeletonId	= skeletonId;

			tktk::DX12GameManager::loadPmd(loadArgs, tktk::MeshDrawFuncRunnerInitParam::create().useBone(true).writeShadowMap(writeShadow));
		}
	}

	void DX12Game::loadMotion(ResourceIdCarrier motionId, const std::string& filePath)
	{
		tktk::DX12GameManager::loadMotionAndAttachId(motionId, filePath);
	}

	void DX12Game::loadSkyBox(ResourceIdCarrier meshId, const std::string& filePath)
	{
		tktk::DX12GameManager::makeSkyBoxMeshAndAttachId(meshId, tktk::DX12GameManager::cpuPriorityLoadTextureBuffer(filePath), tktk::MeshDrawFuncRunnerInitParam::create());
	}

	void DX12Game::loadBoxMesh(ResourceIdCarrier meshId, bool writeShadow, const std::string& filePath)
	{
		tktk::DX12GameManager::makeBoxMeshAndAttachId(meshId, tktk::DX12GameManager::cpuPriorityLoadTextureBuffer(filePath), tktk::MeshDrawFuncRunnerInitParam::create().writeShadowMap(writeShadow));
	}

	size_t DX12Game::getSystemHandle(SystemViewportType type)
	{
		return DX12GameManager::getSystemHandle(type);
	}

	size_t DX12Game::getSystemHandle(SystemScissorRectType type)
	{
		return DX12GameManager::getSystemHandle(type);
	}

	size_t DX12Game::getSystemHandle(SystemVertexBufferType type)
	{
		return DX12GameManager::getSystemHandle(type);
	}

	size_t DX12Game::getSystemHandle(SystemIndexBufferType type)
	{
		return DX12GameManager::getSystemHandle(type);
	}

	size_t DX12Game::getSystemHandle(SystemCBufferType type)
	{
		return DX12GameManager::getSystemHandle(type);
	}

	size_t DX12Game::getSystemHandle(SystemTextureBufferType type)
	{
		return DX12GameManager::getSystemHandle(type);
	}

	size_t DX12Game::getSystemHandle(SystemRtBufferType type)
	{
		return DX12GameManager::getSystemHandle(type);
	}

	size_t DX12Game::getSystemHandle(SystemDsBufferType type)
	{
		return DX12GameManager::getSystemHandle(type);
	}

	size_t DX12Game::getSystemHandle(SystemBasicDescriptorHeapType type)
	{
		return DX12GameManager::getSystemHandle(type);
	}

	size_t DX12Game::getSystemHandle(SystemRtvDescriptorHeapType type)
	{
		return DX12GameManager::getSystemHandle(type);
	}

	size_t DX12Game::getSystemHandle(SystemDsvDescriptorHeapType type)
	{
		return DX12GameManager::getSystemHandle(type);
	}

	size_t DX12Game::getSystemHandle(SystemRootSignatureType type)
	{
		return DX12GameManager::getSystemHandle(type);
	}

	size_t DX12Game::getSystemHandle(SystemPipeLineStateType type)
	{
		return DX12GameManager::getSystemHandle(type);
	}

	size_t DX12Game::getSystemHandle(SystemCameraType type)
	{
		return DX12GameManager::getSystemHandle(type);
	}

	size_t DX12Game::getSystemHandle(SystemLightType type)
	{
		return DX12GameManager::getSystemHandle(type);
	}

	size_t DX12Game::getSystemHandle(SystemMeshType type)
	{
		return DX12GameManager::getSystemHandle(type);
	}

	size_t DX12Game::getSystemHandle(SystemMeshMaterialType type)
	{
		return DX12GameManager::getSystemHandle(type);
	}

	size_t DX12Game::getSystemHandle(SystemPostEffectMaterialType type)
	{
		return DX12GameManager::getSystemHandle(type);
	}
}