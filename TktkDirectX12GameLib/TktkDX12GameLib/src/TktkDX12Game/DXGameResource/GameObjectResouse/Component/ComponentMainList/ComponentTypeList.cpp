#include "TktkDX12Game/DXGameResource/GameObjectResouse/Component/ComponentMainList/ComponentTypeList.h"

#include "TktkDX12Game/DXGameResource/GameObjectResouse/Component/ComponentBase.h"
#include "TktkDX12Game/DXGameResource/GameObjectResouse/Component/ComponentMainList/ComponentListVTable.h"

namespace tktk
{
	ComponentTypeList::ComponentTypeList(ComponentListVTable* vtablePtr)
		: m_vtablePtr(vtablePtr)
	{
	}

	void ComponentTypeList::addComponent(const std::shared_ptr<ComponentBase>& componentPtr)
	{
		m_newComponentList.push_front(componentPtr);
	}

	void ComponentTypeList::activeChangeCheck()
	{
		for (const auto& node : m_mainList)
		{
			if (!node->activeChangeCheck()) continue;

			if (node->isActive())
			{
				m_vtablePtr->onEnable(node);
			}
			else
			{
				m_vtablePtr->onDisable(node);
			}
		}
	}

	void ComponentTypeList::runUpdate()
	{
		m_vtablePtr->update(m_mainList);
	}

	void ComponentTypeList::runBeforeCollide()
	{
		m_vtablePtr->beforeCollide(m_mainList);
	}

	void ComponentTypeList::runAfterCollide()
	{
		m_vtablePtr->afterCollide(m_mainList);
	}

	void ComponentTypeList::moveNewComponent()
	{
		for (const auto& node : m_newComponentList)
		{
			m_mainList.push_front(node);
		}
		m_newComponentList.clear();
	}

	void ComponentTypeList::removeDeadComponent()
	{
		m_mainList.remove_if([this](const auto& node)
		{
			if (node->isDead())
			{
				m_vtablePtr->onDestroy(node);
				return true;
			}
			return false;
		});
	}
}