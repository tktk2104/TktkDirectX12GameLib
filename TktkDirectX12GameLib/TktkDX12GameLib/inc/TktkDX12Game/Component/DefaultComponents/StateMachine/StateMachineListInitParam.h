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
		template <class StateIdType>
		struct Node
		{
		public:

			Node(StateIdType id) : m_id(id) , m_children() {};
			Node(StateIdType id, const std::vector<Node>& children) : m_id(id) , m_children(children) {};

		public:

			StateIdType			m_id;
			std::vector<Node>	m_children;
		};

	public:

		StateMachineListInitParam() = default;

	public:

		template <class StateIdType>
		void initRootNode(std::initializer_list<StateIdType> roots);

		template <class StateIdType>
		void addChildNode(std::initializer_list<StateIdType> hierarchy, std::initializer_list<StateIdType> child);

	public:

		// 一番上の階層の要素
		std::vector<Node<int>>	m_roots;
	};
//┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//┃ここから下はテンプレート関数の実装
//┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

	template<class StateIdType>
	inline void StateMachineListInitParam::initRootNode(std::initializer_list<StateIdType> roots)
	{
		// 一番上の階層の要素の配列のメモリ確保を行う
		m_roots.reserve(roots.size());

		// 変数の初期化を行う
		for (const auto& root : std::vector<StateIdType>(roots))
		{
			m_roots.push_back(static_cast<int>(root));
		}
	}

	template<class StateIdType>
	inline void StateMachineListInitParam::addChildNode(std::initializer_list<StateIdType> hierarchy, std::initializer_list<StateIdType> children)
	{
		auto hierarchyArray = std::vector<StateIdType>(hierarchy);

		Node<int>* curNodePtr = nullptr;

		for (auto& rootsNode : m_roots)
		{
			if (rootsNode.m_id == static_cast<int>(hierarchyArray.at(0U))) curNodePtr = &rootsNode;
		}

		if (curNodePtr == nullptr) return;

		for (size_t i = 1; i < hierarchyArray.size(); i++)
		{
			bool findChild = false;

			for (auto& child : curNodePtr->m_children)
			{
				if (child.m_id == static_cast<int>(hierarchyArray.at(i)))
				{
					findChild = true;
					curNodePtr = &child;
					break;
				}
			}

			if (!findChild) return;
		}

		auto childrenArray = std::vector<StateIdType>(children);

		curNodePtr->m_children.reserve(childrenArray.size());

		for (const auto& id : childrenArray)
		{
			curNodePtr->m_children.push_back(static_cast<int>(id));
		}
	}
}
#endif // !STATE_MACHINE_LIST_INIT_PARAM_H_