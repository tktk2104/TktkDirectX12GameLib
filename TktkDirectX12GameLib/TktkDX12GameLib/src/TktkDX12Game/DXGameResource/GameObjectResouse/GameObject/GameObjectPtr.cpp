#include "TktkDX12Game/DXGameResource/GameObjectResouse/GameObject/GameObjectPtr.h"

namespace tktk
{
	GameObjectPtr::GameObjectPtr(const std::weak_ptr<GameObject>& weakPtr)
		: m_gameObjectPtr(weakPtr)
	{
	}

	bool GameObjectPtr::expired() const
	{
		return m_gameObjectPtr.expired();
	}

	bool GameObjectPtr::isSame(const GameObjectPtr& other) const
	{
		if (expired() && other.expired()) return true;
		if (expired() || other.expired()) return false;
		return m_gameObjectPtr.lock() == other.m_gameObjectPtr.lock();
	}

	std::shared_ptr<GameObject> GameObjectPtr::operator->() const
	{
		if (expired()) return nullptr;
		return m_gameObjectPtr.lock();
	}
}