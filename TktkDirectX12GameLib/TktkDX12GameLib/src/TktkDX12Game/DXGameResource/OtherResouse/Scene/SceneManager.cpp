#include "TktkDX12Game/DXGameResource/OtherResouse/Scene/SceneManager.h"

#include "TktkDX12Game/DXGameResource/OtherResouse/Scene/SceneInstanceCarrier.h"

namespace tktk
{
	SceneManager::SceneManager(const tktkContainer::ResourceContainerInitParam& initParam)
		: m_sceneArray(initParam)
	{
	}

	// デストラクタを非インライン化する
	SceneManager::~SceneManager() = default;

	size_t SceneManager::create(const SceneInitParam& initParam)
	{
		return m_sceneArray.create(initParam);
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