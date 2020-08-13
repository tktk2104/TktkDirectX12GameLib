#include "TktkDX12Game/TktkDX12Game.h"

namespace tktk
{
	const tktkMath::Vector2& DX12Game::getWindowSize()
	{
		// TODO: return ステートメントをここに挿入します
	}

	void DX12Game::enableScene(unsigned int id)
	{
	}

	void DX12Game::disableScene(unsigned int id)
	{
	}

	void DX12Game::SendMessageAll(unsigned int messageId, const MessageAttachment& value)
	{
	}

	GameObjectPtr DX12Game::createGameObject()
	{
		return GameObjectPtr();
	}

	GameObjectPtr DX12Game::findGameObjectWithTagImpl(int tag)
	{
		return GameObjectPtr();
	}

	std::forward_list<GameObjectPtr> DX12Game::findGameObjectsWithTagImpl(int tag)
	{
		return std::forward_list<GameObjectPtr>();
	}

	bool DX12Game::isPush(MouseButtonType buttonType)
	{
		return false;
	}

	bool DX12Game::isTrigger(MouseButtonType buttonType)
	{
		return false;
	}

	tktkMath::Vector2 DX12Game::mousePos()
	{
		return tktkMath::Vector2();
	}

	bool DX12Game::isPush(KeybordKeyType keyType)
	{
		return false;
	}

	bool DX12Game::isTrigger(KeybordKeyType keyType)
	{
		return false;
	}

	tktkMath::Vector2 DX12Game::getLstick()
	{
		return tktkMath::Vector2();
	}

	tktkMath::Vector2 DX12Game::getRstick()
	{
		return tktkMath::Vector2();
	}

	bool DX12Game::isPush(GamePadBtnType btnType)
	{
		return false;
	}

	bool DX12Game::isTrigger(GamePadBtnType btnType)
	{
		return false;
	}

	void DX12Game::reset()
	{
	}

	float DX12Game::deltaTime()
	{
		return 0.0f;
	}

	float DX12Game::noScaleDeltaTime()
	{
		return 0.0f;
	}

	float DX12Game::getCurTimeSec()
	{
		return 0.0f;
	}

	void DX12Game::setMaximumDeltaTime(float maximumDeltaTime)
	{
	}

	float DX12Game::getTimeScale()
	{
		return 0.0f;
	}

	void DX12Game::setTimeScale(float timeScaleRate)
	{
	}

	void DX12Game::setBaseFps(unsigned int baseFps)
	{
	}

	unsigned int DX12Game::getBaseFps()
	{
		return 0;
	}

	float DX12Game::fps()
	{
		return 0.0f;
	}
}