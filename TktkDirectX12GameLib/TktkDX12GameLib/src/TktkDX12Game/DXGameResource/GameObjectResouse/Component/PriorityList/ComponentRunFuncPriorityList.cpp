#include "TktkDX12Game/DXGameResource/GameObjectResouse/Component/PriorityList/ComponentRunFuncPriorityList.h"

namespace tktk
{
	void ComponentRunFuncPriorityList::addPriority(std::type_index type, float priority)
	{
		if (m_updatePriorityMap.count(type) == 0U)
		{
			m_updatePriorityMap.emplace(type, priority);
		}
	}

	float ComponentRunFuncPriorityList::getPriority(std::type_index type) const
	{
		if (m_updatePriorityMap.count(type) == 0U) return BasePriority;
		return m_updatePriorityMap.at(type);
	}
}