#include "TktkDX12Game/DXGameResource/Scene/SceneManager.h"

namespace tktk
{
	SceneManager::SceneManager(const tktkContainer::ResourceContainerInitParam& initParam)
		: m_sceneArray(initParam)
	{
	}

	size_t SceneManager::create(const SceneDataInitParam& initParam)
	{
		return m_sceneArray.create(initParam.scenePtr, initParam.vtablePtr);
	}

	void SceneManager::setSceneEndDestroyGameObjectTag(size_t handle, GameObjectTagCarrier tag)
	{
		m_sceneArray.getMatchHandlePtr(handle)->setSceneEndDestroyGameObjectTag(tag);
	}

	void SceneManager::enable(size_t handle)
	{
		m_sceneArray.getMatchHandlePtr(handle)->enable();
	}

	void SceneManager::disable(size_t handle)
	{
		m_sceneArray.getMatchHandlePtr(handle)->disable();
	}

	void SceneManager::update()
	{
		for (auto& node : m_sceneArray)
		{
			node.changeActive();
		}

		for (auto& node : m_sceneArray)
		{
			node.update();
		}
	}
}