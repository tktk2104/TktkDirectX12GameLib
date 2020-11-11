#include "TktkDX12Game/DXGameResource/GameObjectResouse/Component/ComponentCollisionFunc/ComponentCollisionList.h"

#include "TktkDX12Game/DXGameResource/GameObjectResouse/Component/ComponentBase.h"
#include "TktkDX12Game/DXGameResource/GameObjectResouse/Component/ComponentCollisionFunc/ComponentCollisionFuncRunner.h"

namespace tktk
{
	// コンストラクタを非インライン化する
	ComponentCollisionList::ComponentCollisionList() = default;

	// デストラクタを非インライン化する
	ComponentCollisionList::~ComponentCollisionList() = default;

	void ComponentCollisionList::runCollisionFunc()
	{
		// 前フレームで衝突した相手の情報を更新する
		// ※コンテナの要素を変更する処理な為、非const
		for (auto& collisionFuncRunner : m_collisionList)
		{
			collisionFuncRunner.second.updateHitObjectList();
		}

		// 衝突判定の組み合わせを巡回する
		for (const auto& collisionGroupPair : m_collisionGroupPairArray)
		{
			// １つ目の衝突判定グループの範囲を表すイテレータペア
			auto firstGroup = m_collisionList.equal_range(collisionGroupPair.first);

			// ２つ目の衝突判定グループの範囲を表すイテレータペア
			auto secondGroup = m_collisionList.equal_range(collisionGroupPair.second);

			// １つ目の衝突判定グループを巡回する
			for (auto firstItr = firstGroup.first; firstItr != firstGroup.second; firstItr++)
			{
				// ２つ目の衝突判定グループを巡回する
				for (auto secondItr = secondGroup.first; secondItr != secondGroup.second; secondItr++)
				{
					// １つ目のグループの要素の衝突判定関数を２つ目のグループの要素を引数に実行する
					(*firstItr).second.runCollideFunc((*secondItr).second);
				}
			}
		}
	}

	void ComponentCollisionList::movePreFrameAddedNode()
	{
		// メインリストに移動する要素が入ったリストを巡回
		for (const auto& node : m_nextFrameAddNodeList)
		{
			// メインリストに要素をコピー
			m_collisionList.insert(node);
		}

		// コピー元のコンテナは削除
		m_nextFrameAddNodeList.clear();
	}

	void ComponentCollisionList::removeDeadComponent()
	{
		// メインリストを巡回する
		for (auto itr = std::begin(m_collisionList); itr != std::end(m_collisionList);)
		{
			// もし対象の要素の死亡フラグが立っていたら
			if ((*itr).second.isDead())
			{
				// その要素を削除しイテレータの値を次にチェックする対象に変更する
				itr = m_collisionList.erase(itr);
				continue;
			}
			// イテレータをインクリメント
			++itr;
		}
	}

	void ComponentCollisionList::addCollisionGroup(CollisionGroupTypeCarrier firstGroup, CollisionGroupTypeCarrier secondGroup)
	{
		// 新たな衝突判定グループを追加する
		m_collisionGroupPairArray.push_back(std::make_pair(firstGroup, secondGroup));
	}

	void ComponentCollisionList::add(const ComponentBasePtr& componentPtr, ComponentCollisionFuncVTable* vtablePtr)
	{
		m_nextFrameAddNodeList.emplace_front(std::make_pair(
			componentPtr->getCollisionGroup(),
			ComponentCollisionFuncRunner(componentPtr, vtablePtr)
		));
	}
	
}