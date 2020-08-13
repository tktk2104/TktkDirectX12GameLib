#include "TktkDX12Game/Component/ComponentUpdatePriorityList.h"

namespace tktk
{
	float ComponentUpdatePriorityList::getPriority(unsigned int typeId) const
	{
		if (m_updatePriorityMap.count(typeId) == 0U) return m_basePriority;
		return m_updatePriorityMap.at(typeId);
	}
}