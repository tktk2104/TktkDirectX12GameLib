#ifndef COMPONENT_COLLISION_LIST_H_
#define COMPONENT_COLLISION_LIST_H_

#include <vector>
#include <forward_list>
#include <unordered_map>
#include <TktkTemplateMetaLib/HasFuncCheck/CreatedStruct/HasIsCollideChecker.h>
#include "ComponentCollisionFuncRunner.h"

namespace tktk
{
	// 指定のクラスが変数がisCollide関数を持っているか判定するテンプレートメタのエイリアステンプレート
	template <class ComponentType>
	using has_isCollide = std::enable_if_t<has_isCollide_checker<ComponentType*, bool, const tktk::ComponentBasePtr&>::value>*;
	template <class ComponentType>
	using not_has_isCollide = std::enable_if_t<!has_isCollide_checker<ComponentType*, bool, const tktk::ComponentBasePtr&>::value>*;


	// コンポーネントの衝突判定を行うリスト
	class ComponentCollisionList
	{
	public:

		ComponentCollisionList() = default;

	public:

		// 衝突判定関数を実行する
		void runCollisionFunc();

		// 前フレームに追加されたコンポーネントをメインリストに移動する
		void movePreFrameAddedNode();

		// 死亡フラグが立っているコンポーネントを削除する
		void removeDeadComponent();

		// 衝突判定の組み合わせを追加する
		void addCollisionGroup(int firstGroup, int secondGroup);

	public:

		// 引数のコンポーネントの型が「isCollide()」関数を持っていたら自身のコンテナに追加する
		template <class ComponentType, has_isCollide<ComponentType> = nullptr>
		void addComponent(const std::weak_ptr<ComponentType>& componentPtr);
		template <class ComponentType, not_has_isCollide<ComponentType> = nullptr>
		void addComponent(const std::weak_ptr<ComponentType>& componentPtr);

	private:

		std::vector<std::pair<int, int>>								m_collisionGroupPairArray;
		std::unordered_multimap<int, ComponentCollisionFuncRunner>		m_collisionList;
		std::forward_list<std::pair<int, ComponentCollisionFuncRunner>>	m_nextFrameAddNodeList;
	};
//┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//┃ここから下は関数の実装
//┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

	// 引数のコンポーネントの型が「isCollide()」関数を持っていたら次フレームでメインリストに追加するための一時リストに追加する
	template<class ComponentType, has_isCollide<ComponentType>>
	inline void ComponentCollisionList::addComponent(const std::weak_ptr<ComponentType>& componentPtr)
	{
		m_nextFrameAddNodeList.emplace_front(componentPtr.lock()->getCollisionGroup(), componentPtr);
	}
	template<class ComponentType, not_has_isCollide<ComponentType>>
	inline void ComponentCollisionList::addComponent(const std::weak_ptr<ComponentType>& componentPtr) {}
}
#endif // !COMPONENT_COLLISION_LIST_H_