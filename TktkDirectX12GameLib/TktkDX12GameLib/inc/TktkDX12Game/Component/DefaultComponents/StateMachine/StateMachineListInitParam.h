#ifndef STATE_MACHINE_LIST_INIT_PARAM_H_
#define STATE_MACHINE_LIST_INIT_PARAM_H_

#include <vector>

namespace tktk
{
	// ステートマシンを作るために必要な変数
	struct StateMachineListInitParam
	{
	public:

		// ステートの要素（入れ子構造になっている）
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

		// 一番上の階層の要素
		std::vector<Node>	m_roots;
	};
}
#endif // !STATE_MACHINE_LIST_INIT_PARAM_H_