#include "TktkDX12Game/Component/DefaultComponents/StateMachine/CurStateTypeList.h"

#include <algorithm>

namespace tktk
{
	void CurStateTypeList::stateEnable(StateTypeCarrier stateType)
	{
		m_stateTypeList.push_front(stateType);
	}

	void CurStateTypeList::stateDisable(StateTypeCarrier stateType)
	{
		m_stateTypeList.remove(stateType);
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