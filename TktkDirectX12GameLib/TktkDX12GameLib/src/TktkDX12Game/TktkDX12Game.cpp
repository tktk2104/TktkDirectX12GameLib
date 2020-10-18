#include "TktkDX12Game/TktkDX12Game.h"

#include "TktkDX12Game/_MainManager/DX12GameManager.h"

namespace tktk
{
	const tktkMath::Vector2& DX12Game::getWindowSize()
	{
		return DX12GameManager::getWindowSize();
	}

	GameObjectPtr DX12Game::createGameObject()
	{
		return DX12GameManager::createGameObject();
	}

	bool DX12Game::isPush(MouseButtonType buttonType)
	{
		return DX12GameManager::isPush(buttonType);
	}

	bool DX12Game::isTrigger(MouseButtonType buttonType)
	{
		return DX12GameManager::isTrigger(buttonType);
	}

	tktkMath::Vector2 DX12Game::mousePos()
	{
		return DX12GameManager::mousePos();
	}

	bool DX12Game::isPush(KeybordKeyType keyType)
	{
		return DX12GameManager::isPush(keyType);
	}

	bool DX12Game::isTrigger(KeybordKeyType keyType)
	{
		return DX12GameManager::isTrigger(keyType);
	}

	tktkMath::Vector2 DX12Game::getLstick()
	{
		return DX12GameManager::getLstick();
	}

	tktkMath::Vector2 DX12Game::getRstick()
	{
		return DX12GameManager::getRstick();
	}

	bool DX12Game::isPush(GamePadBtnType buttonType)
	{
		return DX12GameManager::isPush(buttonType);
	}

	bool DX12Game::isTrigger(GamePadBtnType buttonType)
	{
		return DX12GameManager::isTrigger(buttonType);
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

	void DX12Game::enableSceneImpl(int id)
	{
		DX12GameManager::enableScene(DX12GameManager::getSceneHandle(id));
	}

	void DX12Game::disableSceneImpl(int id)
	{
		DX12GameManager::disableScene(DX12GameManager::getSceneHandle(id));
	}

	void DX12Game::sendMessageAllImpl(unsigned int messageId, const MessageAttachment& value)
	{
		DX12GameManager::sendMessageAll(messageId, value);
	}

	GameObjectPtr DX12Game::findGameObjectWithTagImpl(int tag)
	{
		return DX12GameManager::findGameObjectWithTag(tag);
	}

	std::forward_list<GameObjectPtr> DX12Game::findGameObjectsWithTagImpl(int tag)
	{
		return DX12GameManager::findGameObjectsWithTag(tag);
	}

	void DX12Game::destroyGameObjectsWithTagImpl(int tag)
	{
		DX12GameManager::destroyGameObjectsWithTag(tag);
	}
}