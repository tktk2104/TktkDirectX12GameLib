#include "TktkDX12Game/Component/ComponentDrawFunc/ComponentDrawList.h"

namespace tktk
{
	void ComponentDrawList::runDrawFunc() const
	{
		// 描画関数呼び出しクラスを巡回する
		for (const auto& drawFuncRunner : m_drawList)
		{
			// 描画関数を呼ぶ
			drawFuncRunner.second.runDrawFunc();
		}
	}

	void ComponentDrawList::movePreFrameAddedNode()
	{
		// メインリストに移動する要素が入ったリストを巡回
		for (const auto& node : m_nextFrameAddNodeList)
		{
			// メインリストに要素をコピー
			m_drawList.insert(node);
		}

		// コピー元のコンテナは削除
		m_nextFrameAddNodeList.clear();
	}

	void ComponentDrawList::removeDeadComponent()
	{
		// メインリストを巡回する
		for (auto itr = std::begin(m_drawList); itr != std::end(m_drawList);)
		{
			// もし対象の要素の死亡フラグが立っていたら
			if ((*itr).second.isDead())
			{
				// その要素を削除しイテレータの値を次にチェックする対象に変更する
				itr = m_drawList.erase(itr);
				continue;
			}
			// イテレータをインクリメント
			++itr;
		}
	}
}