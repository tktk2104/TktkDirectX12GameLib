#include "TktkDX12Game/Component/DefaultComponents/StateMachine/StateMachineListInitParam.h"

namespace tktk
{
	void StateMachineListInitParam::initRootNode(StateTypeList roots)
	{
		// 一番上の階層の要素の配列のメモリ確保を行う
		m_roots.reserve(roots.list.size());

		// 変数の初期化を行う
		for (const auto& root : roots.list)
		{
			m_roots.push_back(root);
		}
	}

	void StateMachineListInitParam::addChildNode(StateTypeHierarchy hierarchy, StateTypeList child)
	{
		// 現在のステートを表すポインタ
		Node* curNodePtr = nullptr;

		// ステートの階層をループする
		for (const auto& node : hierarchy.hierarchy)
		{
			// 初回ループのみアルゴリズムが違う
			if (curNodePtr == nullptr)
			{
				// 一番上の階層の要素を巡回する
				for (auto& rootsNode : m_roots)
				{
					// ステートの階層の頭を第一引数から取得し、対応するノードを探す
					if (rootsNode.m_id == (*hierarchy.hierarchy.begin())) curNodePtr = &rootsNode;
				}

				// 対応する一番上の階層を取得できなければここで処理を終える
				if (curNodePtr == nullptr) return;

				// 次の要素へ
				continue;
			}

			// 対応する階層を取得できたか？
			bool findChild = false;

			// 現在のステートの子要素をループする
			for (auto& child : curNodePtr->m_children)
			{
				// 子要素のステートと次に進むべき階層のステートが一致したら
				if (child.m_id == node)
				{
					// 対応する階層を取得したフラグを立てる
					findChild = true;

					// 現在のステートを更新する
					curNodePtr = &child;

					// このループを終える
					break;
				}
			}

			// 対応する階層を取得できなければここで処理を終える
			if (!findChild) return;
		}

		// 対象の階層の子要素のコンテナのメモリを確保する
		curNodePtr->m_children.reserve(child.list.size());

		// 対象の階層の子要素のコンテナに要素を追加する
		for (const auto& type : child.list) curNodePtr->m_children.push_back(type);
	}
}