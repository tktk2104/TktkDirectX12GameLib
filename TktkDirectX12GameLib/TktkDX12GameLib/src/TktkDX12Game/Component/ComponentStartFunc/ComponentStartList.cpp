#include "TktkDX12Game/Component/ComponentStartFunc/ComponentStartList.h"

namespace tktk
{
	void ComponentStartList::runStartFunc()
	{
		// 開始時関数呼び出しクラスを巡回する
		// ※リストの要素を変更するので非const
		for (auto& startFuncRunner : m_startList)
		{
			// 開始時関数を呼ぶ
			startFuncRunner.runStart();
		}
	}

	void ComponentStartList::movePreFrameAddedNode()
	{
		// メインリストに移動する情報が入ったリストの要素をメインリストに移動
		for (const auto& node : m_nextFrameAddNodeList)
		{
			m_startList.push_front(node);
		}

		// コピー元のコンテナは削除
		m_nextFrameAddNodeList.clear();
	}

	void ComponentStartList::removeDeadComponent()
	{
		// 死亡フラグの立ったコンポーネントをリストから削除する
		m_startList.remove_if([](const auto& node) { return node.isDead(); });
	}
}