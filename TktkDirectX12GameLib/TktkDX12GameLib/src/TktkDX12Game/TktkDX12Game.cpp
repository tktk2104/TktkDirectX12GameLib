#include "TktkDX12Game/TktkDX12Game.h"

#include "TktkDX12Game/_MainManager/DX12GameManager.h"

namespace tktk
{
	const tktkMath::Vector2& DX12Game::getWindowSize()
	{
		return DX12GameManager::getWindowSize();
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

	bool DX12Game::isPushImpl(int commandId)
	{
		return DX12GameManager::isPushCommand(commandId);
	}

	bool DX12Game::isPushImpl(MouseButtonType buttonType)
	{
		return DX12GameManager::isMousePush(buttonType);
	}

	bool DX12Game::isPushImpl(KeybordKeyType keyType)
	{
		return DX12GameManager::isKeybordPush(keyType);
	}

	bool DX12Game::isPushImpl(GamePadBtnType btnType)
	{
		return DX12GameManager::isPadPush(btnType);
	}

	bool DX12Game::isTriggerImpl(int commandId)
	{
		return DX12GameManager::isTriggerCommand(commandId);
	}

	bool DX12Game::isTriggerImpl(MouseButtonType buttonType)
	{
		return DX12GameManager::isMouseTrigger(buttonType);
	}

	bool DX12Game::isTriggerImpl(KeybordKeyType keyType)
	{
		return DX12GameManager::isKeybordTrigger(keyType);
	}

	bool DX12Game::isTriggerImpl(GamePadBtnType btnType)
	{
		return DX12GameManager::isPadTrigger(btnType);
	}
}