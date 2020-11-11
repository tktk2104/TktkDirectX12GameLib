#include "TktkDX12Game/UtilityProcessManager/UtilityProcessManager.h"

#include "TktkDX12Game/UtilityProcessManager/InputManager/InputManager.h"
#include "TktkDX12Game/UtilityProcessManager/TimeManager/ElapsedTimer.h"
#include "TktkDX12Game/UtilityProcessManager/ResourceHandleGetter/ResourceHandleGetter.h"

namespace tktk
{
	UtilityProcessManager::UtilityProcessManager(HINSTANCE hInstance, HWND handle, float padStickPlayWidth)
	{
		m_inputManager			= std::make_unique<InputManager>(hInstance, handle, padStickPlayWidth);
		m_elapsedTimer			= std::make_unique<ElapsedTimer>();
		m_resourceHandleGetter	= std::make_unique<ResourceHandleGetter>();
	}

	// デストラクタを非インライン化する
	UtilityProcessManager::~UtilityProcessManager() = default;

	void UtilityProcessManager::update()
	{
		m_inputManager->update();
		m_elapsedTimer->update();
	}

	bool UtilityProcessManager::isPush(CommandIdCarrier commandId) const
	{
		return m_inputManager->isPush(commandId);
	}

	bool UtilityProcessManager::isTrigger(CommandIdCarrier commandId) const
	{
		return m_inputManager->isTrigger(commandId);
	}

	const tktkMath::Vector2& UtilityProcessManager::moveVec() const
	{
		return m_inputManager->moveVec();
	}

	const tktkMath::Vector2& UtilityProcessManager::lookVec() const
	{
		return m_inputManager->lookVec();
	}

	bool UtilityProcessManager::isPush(MouseBtnType btnType) const
	{
		return m_inputManager->isPush(btnType);
	}

	bool UtilityProcessManager::isTrigger(MouseBtnType btnType) const
	{
		return m_inputManager->isTrigger(btnType);
	}

	tktkMath::Vector2 UtilityProcessManager::mousePos(HWND hWnd) const
	{
		return m_inputManager->mousePos(hWnd);
	}

	bool UtilityProcessManager::isPush(KeybordKeyType keyType) const
	{
		return m_inputManager->isPush(keyType);
	}

	bool UtilityProcessManager::isTrigger(KeybordKeyType keyType) const
	{
		return m_inputManager->isTrigger(keyType);
	}

	tktkMath::Vector2 UtilityProcessManager::getLstick() const
	{
		return m_inputManager->getLstick();
	}

	tktkMath::Vector2 UtilityProcessManager::getRstick() const
	{
		return m_inputManager->getRstick();
	}

	bool UtilityProcessManager::isPush(GamePadBtnType btnType) const
	{
		return m_inputManager->isPush(btnType);
	}

	bool UtilityProcessManager::isTrigger(GamePadBtnType btnType) const
	{
		return m_inputManager->isTrigger(btnType);
	}

	void UtilityProcessManager::addCommand(CommandIdCarrier commandId, MouseBtnType btnType)
	{
		m_inputManager->addCommand(commandId, btnType);
	}

	void UtilityProcessManager::addCommand(CommandIdCarrier commandId, KeybordKeyType keyType)
	{
		m_inputManager->addCommand(commandId, keyType);
	}

	void UtilityProcessManager::addCommand(CommandIdCarrier commandId, GamePadBtnType btnType)
	{
		m_inputManager->addCommand(commandId, btnType);
	}

	void UtilityProcessManager::addDirectionCommand(DirectionCommandId directionCommandId, MouseBtnType btnType)
	{
		m_inputManager->addDirectionCommand(directionCommandId, btnType);
	}

	void UtilityProcessManager::addDirectionCommand(DirectionCommandId directionCommandId, KeybordKeyType keyType)
	{
		m_inputManager->addDirectionCommand(directionCommandId, keyType);
	}

	void UtilityProcessManager::addDirectionCommand(DirectionCommandId directionCommandId, GamePadBtnType btnType)
	{
		m_inputManager->addDirectionCommand(directionCommandId, btnType);
	}

	void UtilityProcessManager::resetElapsedTime()
	{
		m_elapsedTimer->reset();
	}

	float UtilityProcessManager::deltaTime()
	{
		return m_elapsedTimer->deltaTime();
	}

	float UtilityProcessManager::noScaleDeltaTime()
	{
		return m_elapsedTimer->noScaleDeltaTime();
	}

	float UtilityProcessManager::getCurTimeSec()
	{
		return m_elapsedTimer->getCurTimeSec();
	}

	void UtilityProcessManager::setMaximumDeltaTime(float maximumDeltaTime)
	{
		m_elapsedTimer->setMaximumDeltaTime(maximumDeltaTime);
	}

	float UtilityProcessManager::getTimeScale()
	{
		return m_elapsedTimer->getTimeScale();
	}

	void UtilityProcessManager::setTimeScale(float timeScaleRate)
	{
		m_elapsedTimer->setTimeScale(timeScaleRate);
	}

	void UtilityProcessManager::setBaseFps(unsigned int baseFps)
	{
		m_elapsedTimer->setBaseFps(baseFps);
	}

	unsigned int UtilityProcessManager::getBaseFps()
	{
		return m_elapsedTimer->getBaseFps();
	}

	float UtilityProcessManager::fps()
	{
		return m_elapsedTimer->fps();
	}

	size_t UtilityProcessManager::getSystemHandle(SystemViewportType type) const
	{
		return m_resourceHandleGetter->getSystemHandle(type);
	}

	size_t UtilityProcessManager::getSystemHandle(SystemScissorRectType type) const
	{
		return m_resourceHandleGetter->getSystemHandle(type);
	}

	size_t UtilityProcessManager::getSystemHandle(SystemVertexBufferType type) const
	{
		return m_resourceHandleGetter->getSystemHandle(type);
	}

	size_t UtilityProcessManager::getSystemHandle(SystemIndexBufferType type) const
	{
		return m_resourceHandleGetter->getSystemHandle(type);
	}

	size_t UtilityProcessManager::getSystemHandle(SystemCBufferType type) const
	{
		return m_resourceHandleGetter->getSystemHandle(type);
	}

	size_t UtilityProcessManager::getSystemHandle(SystemTextureBufferType type) const
	{
		return m_resourceHandleGetter->getSystemHandle(type);
	}

	size_t UtilityProcessManager::getSystemHandle(SystemRtBufferType type) const
	{
		return m_resourceHandleGetter->getSystemHandle(type);
	}

	size_t UtilityProcessManager::getSystemHandle(SystemDsBufferType type) const
	{
		return m_resourceHandleGetter->getSystemHandle(type);
	}

	size_t UtilityProcessManager::getSystemHandle(SystemBasicDescriptorHeapType type) const
	{
		return m_resourceHandleGetter->getSystemHandle(type);
	}

	size_t UtilityProcessManager::getSystemHandle(SystemRtvDescriptorHeapType type) const
	{
		return m_resourceHandleGetter->getSystemHandle(type);
	}

	size_t UtilityProcessManager::getSystemHandle(SystemDsvDescriptorHeapType type) const
	{
		return m_resourceHandleGetter->getSystemHandle(type);
	}

	size_t UtilityProcessManager::getSystemHandle(SystemRootSignatureType type) const
	{
		return m_resourceHandleGetter->getSystemHandle(type);
	}

	size_t UtilityProcessManager::getSystemHandle(SystemPipeLineStateType type) const
	{
		return m_resourceHandleGetter->getSystemHandle(type);
	}

	size_t UtilityProcessManager::getSystemHandle(SystemCameraType type) const
	{
		return m_resourceHandleGetter->getSystemHandle(type);
	}

	size_t UtilityProcessManager::getSystemHandle(SystemLightType type) const
	{
		return m_resourceHandleGetter->getSystemHandle(type);
	}

	size_t UtilityProcessManager::getSystemHandle(SystemBasicMeshType type) const
	{
		return m_resourceHandleGetter->getSystemHandle(type);
	}

	size_t UtilityProcessManager::getSystemHandle(SystemBasicMeshMaterialType type) const
	{
		return m_resourceHandleGetter->getSystemHandle(type);
	}

	size_t UtilityProcessManager::getSystemHandle(SystemPostEffectMaterialType type) const
	{
		return m_resourceHandleGetter->getSystemHandle(type);
	}

	void UtilityProcessManager::setSystemHandle(SystemViewportType type, size_t handle)
	{
		m_resourceHandleGetter->setSystemHandle(type, handle);
	}

	void UtilityProcessManager::setSystemHandle(SystemScissorRectType type, size_t handle)
	{
		m_resourceHandleGetter->setSystemHandle(type, handle);
	}

	void UtilityProcessManager::setSystemHandle(SystemVertexBufferType type, size_t handle)
	{
		m_resourceHandleGetter->setSystemHandle(type, handle);
	}

	void UtilityProcessManager::setSystemHandle(SystemIndexBufferType type, size_t handle)
	{
		m_resourceHandleGetter->setSystemHandle(type, handle);
	}

	void UtilityProcessManager::setSystemHandle(SystemCBufferType type, size_t handle)
	{
		m_resourceHandleGetter->setSystemHandle(type, handle);
	}

	void UtilityProcessManager::setSystemHandle(SystemTextureBufferType type, size_t handle)
	{
		m_resourceHandleGetter->setSystemHandle(type, handle);
	}

	void UtilityProcessManager::setSystemHandle(SystemRtBufferType type, size_t handle)
	{
		m_resourceHandleGetter->setSystemHandle(type, handle);
	}

	void UtilityProcessManager::setSystemHandle(SystemDsBufferType type, size_t handle)
	{
		m_resourceHandleGetter->setSystemHandle(type, handle);
	}

	void UtilityProcessManager::setSystemHandle(SystemBasicDescriptorHeapType type, size_t handle)
	{
		m_resourceHandleGetter->setSystemHandle(type, handle);
	}

	void UtilityProcessManager::setSystemHandle(SystemRtvDescriptorHeapType type, size_t handle)
	{
		m_resourceHandleGetter->setSystemHandle(type, handle);
	}

	void UtilityProcessManager::setSystemHandle(SystemDsvDescriptorHeapType type, size_t handle)
	{
		m_resourceHandleGetter->setSystemHandle(type, handle);
	}

	void UtilityProcessManager::setSystemHandle(SystemRootSignatureType type, size_t handle)
	{
		m_resourceHandleGetter->setSystemHandle(type, handle);
	}

	void UtilityProcessManager::setSystemHandle(SystemPipeLineStateType type, size_t handle)
	{
		m_resourceHandleGetter->setSystemHandle(type, handle);
	}

	void UtilityProcessManager::setSystemHandle(SystemCameraType type, size_t handle)
	{
		m_resourceHandleGetter->setSystemHandle(type, handle);
	}

	void UtilityProcessManager::setSystemHandle(SystemLightType type, size_t handle)
	{
		m_resourceHandleGetter->setSystemHandle(type, handle);
	}

	void UtilityProcessManager::setSystemHandle(SystemBasicMeshType type, size_t handle)
	{
		m_resourceHandleGetter->setSystemHandle(type, handle);
	}

	void UtilityProcessManager::setSystemHandle(SystemBasicMeshMaterialType type, size_t handle)
	{
		m_resourceHandleGetter->setSystemHandle(type, handle);
	}

	void UtilityProcessManager::setSystemHandle(SystemPostEffectMaterialType type, size_t handle)
	{
		m_resourceHandleGetter->setSystemHandle(type, handle);
	}

	size_t UtilityProcessManager::getSceneHandle(ResourceIdCarrier id) const
	{
		return m_resourceHandleGetter->getSceneHandle(id);
	}

	size_t UtilityProcessManager::getSoundHandle(ResourceIdCarrier id) const
	{
		return m_resourceHandleGetter->getSoundHandle(id);
	}

	size_t UtilityProcessManager::getPostEffectMaterialHandle(ResourceIdCarrier id) const
	{
		return m_resourceHandleGetter->getPostEffectMaterialHandle(id);
	}

	size_t UtilityProcessManager::getSpriteMaterialHandle(ResourceIdCarrier id) const
	{
		return m_resourceHandleGetter->getSpriteMaterialHandle(id);
	}

	size_t UtilityProcessManager::getLine2DMaterialHandle(ResourceIdCarrier id) const
	{
		return m_resourceHandleGetter->getLine2DMaterialHandle(id);
	}

	size_t UtilityProcessManager::getBillboardMaterialHandle(ResourceIdCarrier id) const
	{
		return m_resourceHandleGetter->getBillboardMaterialHandle(id);
	}

	size_t UtilityProcessManager::getSkeletonHandle(ResourceIdCarrier id) const
	{
		return m_resourceHandleGetter->getSkeletonHandle(id);
	}

	size_t UtilityProcessManager::getMotionHandle(ResourceIdCarrier id) const
	{
		return m_resourceHandleGetter->getMotionHandle(id);
	}

	size_t UtilityProcessManager::getBasicMeshHandle(ResourceIdCarrier id) const
	{
		return m_resourceHandleGetter->getBasicMeshHandle(id);
	}

	size_t UtilityProcessManager::getBasicMeshMaterialHandle(ResourceIdCarrier id) const
	{
		return m_resourceHandleGetter->getBasicMeshMaterialHandle(id);
	}

	size_t UtilityProcessManager::getCameraHandle(ResourceIdCarrier id) const
	{
		return m_resourceHandleGetter->getCameraHandle(id);
	}

	size_t UtilityProcessManager::getLightHandle(ResourceIdCarrier id) const
	{
		return m_resourceHandleGetter->getLightHandle(id);
	}

	void UtilityProcessManager::setSceneHandle(ResourceIdCarrier id, size_t handle)
	{
		m_resourceHandleGetter->setSceneHandle(id, handle);
	}

	void UtilityProcessManager::setSoundHandle(ResourceIdCarrier id, size_t handle)
	{
		m_resourceHandleGetter->setSoundHandle(id, handle);
	}

	void UtilityProcessManager::setPostEffectMaterialHandle(ResourceIdCarrier id, size_t handle)
	{
		m_resourceHandleGetter->setPostEffectMaterialHandle(id, handle);
	}

	void UtilityProcessManager::setSpriteMaterialHandle(ResourceIdCarrier id, size_t handle)
	{
		m_resourceHandleGetter->setSpriteMaterialHandle(id, handle);
	}

	void UtilityProcessManager::setLine2DMaterialHandle(ResourceIdCarrier id, size_t handle)
	{
		m_resourceHandleGetter->setLine2DMaterialHandle(id, handle);
	}

	void UtilityProcessManager::setBillboardMaterialHandle(ResourceIdCarrier id, size_t handle)
	{
		m_resourceHandleGetter->setBillboardMaterialHandle(id, handle);
	}

	void UtilityProcessManager::setSkeletonHandle(ResourceIdCarrier id, size_t handle)
	{
		m_resourceHandleGetter->setSkeletonHandle(id, handle);
	}

	void UtilityProcessManager::setMotionHandle(ResourceIdCarrier id, size_t handle)
	{
		m_resourceHandleGetter->setMotionHandle(id, handle);
	}

	void UtilityProcessManager::setBasicMeshHandle(ResourceIdCarrier id, size_t handle)
	{
		m_resourceHandleGetter->setBasicMeshHandle(id, handle);
	}

	void UtilityProcessManager::setBasicMeshMaterialHandle(ResourceIdCarrier id, size_t handle)
	{
		m_resourceHandleGetter->setBasicMeshMaterialHandle(id, handle);
	}

	void UtilityProcessManager::setCameraHandle(ResourceIdCarrier id, size_t handle)
	{
		m_resourceHandleGetter->setCameraHandle(id, handle);
	}

	void UtilityProcessManager::setLightHandle(ResourceIdCarrier id, size_t handle)
	{
		m_resourceHandleGetter->setLightHandle(id, handle);
	}
}