#ifndef STATE_MACHINE_LIST_INIT_PARAM_H_
#define STATE_MACHINE_LIST_INIT_PARAM_H_

#include <vector>
#include "StateTypeList.h"
#include "StateTypeHierarchy.h"

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

			Node(StateTypeCarrier id) 
				: m_id(id) , m_children() {};
			Node(StateTypeCarrier id, const std::vector<Node>& children) 
				: m_id(id) , m_children(children) {};

		public:

			StateTypeCarrier	m_id;
			std::vector<Node>	m_children;
		};

	public:

		// デフォルトコンストラクタ
		StateMachineListInitParam() = default;

	public:

		// 一番上の階層のステートを設定する
		void initRootNode(StateTypeList roots);

		// 指定の階層のステートに子ステートを追加する
		void addChildNode(StateTypeHierarchy hierarchy, StateTypeList child);

	public:

		// 一番上の階層の要素
		std::vector<Node>	m_roots;
	};
}
#endif // !STATE_MACHINE_LIST_INIT_PARAM_H_