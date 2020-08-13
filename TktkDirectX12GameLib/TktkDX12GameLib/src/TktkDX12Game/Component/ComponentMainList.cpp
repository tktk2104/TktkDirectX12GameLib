#include "TktkDX12Game/Component/ComponentMainList.h"

#include "TktkDX12Game/Component/ComponentBase.h"

namespace tktk
{
	void ComponentMainList::activeChangeCheck()
	{
		for (const auto& node : m_mainList)
		{
			if (!node->activeChangeCheck()) continue;

			if (node->isActive())
			{
				m_vtablePtr->runOnEnable(node);
			}
			else
			{
				m_vtablePtr->runOnDisable(node);
			}
		}
	}

	void ComponentMainList::runUpdate()
	{
		m_vtablePtr->runUpdate(m_mainList);
	}

	void ComponentMainList::runAfterCollide()
	{
		m_vtablePtr->runAfterCollide(m_mainList);
	}

	void ComponentMainList::moveNewComponent()
	{
		for (const auto& node : m_newComponentList)
		{
			m_mainList.push_front(node);
		}
		m_newComponentList.clear();
	}

	void ComponentMainList::removeDeadComponent()
	{
		m_mainList.remove_if([this](const auto& node)
		{
			if (node->isDead())
			{
				m_vtablePtr->runOnDestroy(node);
				return true;
			}
			return false;
		});
	}
}