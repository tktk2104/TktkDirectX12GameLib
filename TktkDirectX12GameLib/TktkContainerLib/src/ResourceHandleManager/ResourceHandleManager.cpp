#include "TktkContainer/ResourceHandleManager/ResourceHandleManager.h"

namespace tktkContainer
{
	unsigned int ResourceHandleManager::createHandle()
	{
		unsigned int handle = 0U;

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

	void ResourceHandleManager::endUseHandle(unsigned int deleteHandle)
	{
		m_endUseHandles.push(deleteHandle);
	}

	void ResourceHandleManager::reset()
	{
		m_endUseHandles = std::queue<unsigned int>();
		m_nextUseHandle = std::numeric_limits<unsigned int>::max();
	}
}