#include "TktkDX12Game/DXGameResource/Scene/SceneManager.h"

namespace tktk
{
	SceneManager::SceneManager(unsigned int sceneNum)
		: m_sceneArray(sceneNum)
	{
	}

	void SceneManager::create(unsigned int id, const std::shared_ptr<SceneBase>& scenePtr, SceneVTable* vtablePtr)
	{
		m_sceneArray.emplaceAt(id, scenePtr, vtablePtr);
	}

	void SceneManager::enable(unsigned int id)
	{
		m_sceneArray.at(id)->enable();
	}

	void SceneManager::disable(unsigned int id)
	{
		m_sceneArray.at(id)->disable();
	}

	void SceneManager::update()
	{
		for (auto& node : m_sceneArray)
		{
			node.update();
		}
	}
}