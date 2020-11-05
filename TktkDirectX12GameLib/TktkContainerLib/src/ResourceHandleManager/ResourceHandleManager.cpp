#include "TktkContainer/ResourceHandleManager/ResourceHandleManager.h"

namespace tktkContainer
{
	size_t ResourceHandleManager::createHandle()
	{
		size_t handle = 0U;

		if (m_endUseHandles.empty())
		{
			handle = m_nextUseHandle--;
		}
		else
		{
			handle = m_endUseHandles.front();
			m_endUseHandles.pop();
		}
		return handle;
	}

	void ResourceHandleManager::endUseHandle(size_t deleteHandle)
	{
		m_endUseHandles.push(deleteHandle);
	}

	void ResourceHandleManager::reset()
	{
		m_endUseHandles = std::queue<size_t>();
		m_nextUseHandle = std::numeric_limits<size_t>::max();
	}
}