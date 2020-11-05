#include "TktkDX12Game/DXGameResource/Scene/SceneInstanceCarrier.h"

#include "TktkDX12Game/_MainManager/DX12GameManager.h"

namespace tktk
{
	SceneInstanceCarrier::SceneInstanceCarrier(const std::shared_ptr<SceneBase> & scenePtr, SceneVTable* vtablePtr)
		: m_scenePtr(scenePtr)
		, m_vtablePtr(vtablePtr)
	{
	}

	SceneInstanceCarrier::~SceneInstanceCarrier()
	{
		if ((m_scenePtr != nullptr) && m_isActive)
		{
			m_vtablePtr->end(m_scenePtr);
		}

		if (m_destroyGameObjectTag != nullptr)
		{
			DX12GameManager::destroyGameObjectsWithTag(*m_destroyGameObjectTag);
		}
	}

	SceneInstanceCarrier::SceneInstanceCarrier(SceneInstanceCarrier&& other) noexcept
		: m_isActive(other.m_isActive)
		, m_nextFrameIsActive(other.m_nextFrameIsActive)
		, m_runAfterChangeActiveFunc(other.m_runAfterChangeActiveFunc)
		, m_scenePtr(std::move(other.m_scenePtr))
		, m_vtablePtr(other.m_vtablePtr)
	{
		other.m_scenePtr = nullptr;
	}

	void SceneInstanceCarrier::setSceneEndDestroyGameObjectTag(GameObjectTagCarrier tag)
	{
		m_destroyGameObjectTag = std::make_unique<GameObjectTagCarrier>(tag);
	}

	void SceneInstanceCarrier::enable()
	{
		m_nextFrameIsActive = true;
	}

	void SceneInstanceCarrier::disable()
	{
		m_nextFrameIsActive = false;
	}

	void SceneInstanceCarrier::changeActive()
	{
		if (m_scenePtr == nullptr) return;

		if (m_isActive != m_nextFrameIsActive)
		{
			m_isActive = m_nextFrameIsActive;

			m_runAfterChangeActiveFunc = true;
		}
	}

	void SceneInstanceCarrier::update()
	{
		if (m_scenePtr == nullptr) return;

		if (m_runAfterChangeActiveFunc)
		{
			if (m_isActive) m_vtablePtr->start(m_scenePtr);
			else			m_vtablePtr->end(m_scenePtr);

			m_runAfterChangeActiveFunc = false;
		}

		if (m_isActive)		m_vtablePtr->update(m_scenePtr);
	}
}