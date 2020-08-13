#ifndef COMPONENT_COLLISION_LIST_H_
#define COMPONENT_COLLISION_LIST_H_

#include <array>
#include <unordered_map>
#include <TktkTemplateMetaLib/HasFuncCheck/CreatedStruct/HasIsCollideChecker.h>
#include "ComponentCollisionFuncRunner.h"

namespace tktk
{
	// コンポーネントの衝突判定を行うリスト
	class ComponentCollisionList
	{
	public:

		ComponentCollisionList() = default;

	public:

		// 衝突判定関数を実行する
		void runCollisionFunc();

		// 前フレームに追加されたコンポーネントをメインリストに追加する
		void moveNewComponent();

		// 死亡フラグが立っているコンポーネントを削除する
		void removeDeadComponent();

	public:

		// 衝突判定の組み合わせを追加する
		void addCollisionGroup(int firstGroup, int secondGroup);

		// 引数のコンポーネントの型が「isCollide()」関数を持っていたら自身のコンテナに追加する
		template <class ComponentType, std::enable_if_t<has_isCollide_checker<ComponentType*, bool, const tktk::ComponentBasePtr&>::value>* = nullptr>
		void addComponent(const std::weak_ptr<ComponentType>& componentPtr);
		template <class ComponentType, std::enable_if_t<!has_isCollide_checker<ComponentType*, bool, const tktk::ComponentBasePtr&>::value>* = nullptr>
		void addComponent(const std::weak_ptr<ComponentType>& componentPtr);

	private:

		std::vector<std::pair<int, int>>							m_collisionGroupPairArray;
		std::unordered_multimap<int, ComponentCollisionFuncRunner>	m_collisionList;
		std::unordered_multimap<int, ComponentCollisionFuncRunner>	m_newComponentList;
	};
//┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//┃ここから下は関数の実装
//┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

	// 引数のコンポーネントの型が「isCollide()」関数を持っていたら自身のコンテナに追加する
	template<class ComponentType, std::enable_if_t<has_isCollide_checker<ComponentType*, bool, const tktk::ComponentBasePtr&>::value>*>
	inline void ComponentCollisionList::addComponent(const std::weak_ptr<ComponentType>& componentPtr)
	{
		m_newComponentList.emplace(componentPtr.lock()->getCollisionGroup(), componentPtr);
	}
	template<class ComponentType, std::enable_if_t<!has_isCollide_checker<ComponentType*, bool, const tktk::ComponentBasePtr&>::value>*>
	inline void ComponentCollisionList::addComponent(const std::weak_ptr<ComponentType>& componentPtr) {}
}
#endif // !COMPONENT_COLLISION_LIST_H_