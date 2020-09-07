#include "TktkDX12Game/DXGameResource/Scene/SceneManager.h"

namespace tktk
{
	SceneManager::SceneManager(const tktkContainer::ResourceContainerInitParam& initParam)
		: m_sceneArray(initParam)
	{
	}

	unsigned int SceneManager::create(const std::shared_ptr<SceneBase>& scenePtr, SceneVTable* vtablePtr)
	{
		return m_sceneArray.create(scenePtr, vtablePtr);
	}

	void SceneManager::enable(unsigned int handle)
	{
		m_sceneArray.getMatchHandlePtr(handle)->enable();
	}

	void SceneManager::disable(unsigned int handle)
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