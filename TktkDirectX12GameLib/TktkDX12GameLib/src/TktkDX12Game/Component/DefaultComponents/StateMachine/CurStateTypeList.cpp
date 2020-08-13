#include "TktkDX12Game/Component/DefaultComponents/StateMachine/CurStateTypeList.h"

#include <algorithm>

namespace tktk
{
	void CurStateTypeList::addState(int stateType)
	{
		m_stateTypeList.push_front(stateType);
	}

	void CurStateTypeList::removeState(int stateType)
	{
		m_stateTypeList.remove(stateType);
	}

	void CurStateTypeList::clearState()
	{
		m_stateTypeList.clear();
	}

	bool CurStateTypeList::contain(int stateType)
	{
		auto begin = std::begin(m_stateTypeList);
		auto end = std::end(m_stateTypeList);
		auto result = std::find(begin, end, stateType);
		return (result != end);
	}
}