#include "TktkDX12Game/DXGameResource/GameObjectResouse/Component/DefaultComponents/StateMachine/CurStateTypeList.h"

/* std::find */
#include <algorithm>

namespace tktk
{
	void CurStateTypeList::stateEnable(StateTypeCarrier stateType)
	{
		m_stateTypeList.insert(stateType);
	}

	void CurStateTypeList::stateDisable(StateTypeCarrier stateType)
	{
		m_stateTypeList.erase(stateType);
	}

	void CurStateTypeList::clearState()
	{
		m_stateTypeList.clear();
	}

	bool CurStateTypeList::contain(StateTypeCarrier stateType) const
	{
		auto end = std::end(m_stateTypeList);
		auto result = std::find(std::begin(m_stateTypeList), end, stateType);
		return (result != end);
	}
}