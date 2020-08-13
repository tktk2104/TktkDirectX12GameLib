#ifndef STATE_MACHINE_LIST_INIT_PARAM_H_
#define STATE_MACHINE_LIST_INIT_PARAM_H_

#include <vector>

namespace tktk
{
	struct StateMachineListInitParam
	{
	public:

		struct Node
		{
		public:

			Node(int id);
			Node(int id, const std::vector<Node>& child);

		public:

			int					m_id;
			std::vector<Node>	m_child;
		};

	public:

		StateMachineListInitParam(const std::vector<Node>& roots);

	public:

		std::vector<Node>	m_roots;
	};
}
#endif // !STATE_MACHINE_LIST_INIT_PARAM_H_