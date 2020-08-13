#include "TktkDX12Game/Component/DefaultComponents/StateMachine/StateMachineListInitParam.h"

namespace tktk
{
	StateMachineListInitParam::Node::Node(int id)
		: m_id(id)
		, m_child()
	{
	}

	StateMachineListInitParam::Node::Node(int id, const std::vector<Node>& child)
		: m_id(id)
		, m_child(child)
	{
	}

	StateMachineListInitParam::StateMachineListInitParam(const std::vector<Node>& roots)
		: m_roots(roots)
	{
	}
}