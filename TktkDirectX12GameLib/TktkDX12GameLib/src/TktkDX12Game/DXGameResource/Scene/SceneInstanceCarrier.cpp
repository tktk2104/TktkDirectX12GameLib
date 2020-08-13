#include "TktkDX12Game/DXGameResource/Scene/SceneInstanceCarrier.h"

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
	}

	void SceneInstanceCarrier::enable()
	{
		m_nextFrameIsActive = true;
	}

	void SceneInstanceCarrier::disable()
	{
		m_nextFrameIsActive = false;
	}

	void SceneInstanceCarrier::update()
	{
		if (m_scenePtr == nullptr) return;

		if (m_isActive != m_nextFrameIsActive)
		{
			m_isActive = m_nextFrameIsActive;

			if (m_isActive) m_vtablePtr->start(m_scenePtr);
			else			m_vtablePtr->end(m_scenePtr);
		}

		if (m_isActive)		m_vtablePtr->update(m_scenePtr);
	}
}