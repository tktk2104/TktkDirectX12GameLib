#include "TktkDX12Game/Component/DefaultComponents/StateMachine/CurStateTypeList.h"

#include <algorithm>

namespace tktk
{
	void CurStateTypeList::stateEnable(int stateType)
	{
		m_stateTypeList.push_front(stateType);
	}

	void CurStateTypeList::stateDisable(int stateType)
	{
		m_stateTypeList.remove(stateType);
	}

	void CurStateTypeList::clearState()
	{
		m_stateTypeList.clear();
	}

	bool CurStateTypeList::contain(int stateType) const
	{
		auto end = std::end(m_stateTypeList);
		auto result = std::find(std::begin(m_stateTypeList), end, stateType);
		return (result != end);
	}
}