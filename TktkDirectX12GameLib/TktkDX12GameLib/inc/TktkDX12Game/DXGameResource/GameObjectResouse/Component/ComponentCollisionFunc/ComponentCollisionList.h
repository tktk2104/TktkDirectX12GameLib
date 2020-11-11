#ifndef COMPONENT_COLLISION_LIST_H_
#define COMPONENT_COLLISION_LIST_H_

/* std::vector */
#include <vector>

/* std::forward_list */
#include <forward_list>

/* std::unordered_multimap */
#include <unordered_map>

/* class member */
#include "CollisionGroupTypeCarrier.h"

namespace tktk
{
	class ComponentCollisionFuncRunner;
	class ComponentBasePtr;
	struct ComponentCollisionFuncVTable;

	// コンポーネントの衝突判定を行うリスト
	class ComponentCollisionList
	{
	public:

		ComponentCollisionList();
		~ComponentCollisionList();

	public:

		// 衝突判定関数を実行する
		void runCollisionFunc();

		// 前フレームに追加されたコンポーネントをメインリストに移動する
		void movePreFrameAddedNode();

		// 死亡フラグが立っているコンポーネントを削除する
		void removeDeadComponent();

		// 衝突判定の組み合わせを追加する
		void addCollisionGroup(CollisionGroupTypeCarrier firstGroup, CollisionGroupTypeCarrier secondGroup);

	public:

		void add(const ComponentBasePtr& componentPtr, ComponentCollisionFuncVTable* vtablePtr);

	private:

		std::vector<std::pair<CollisionGroupTypeCarrier, CollisionGroupTypeCarrier>>			m_collisionGroupPairArray;
		std::unordered_multimap<CollisionGroupTypeCarrier, ComponentCollisionFuncRunner>		m_collisionList;
		std::forward_list<std::pair<CollisionGroupTypeCarrier, ComponentCollisionFuncRunner>>	m_nextFrameAddNodeList;
	};
}
#endif // !COMPONENT_COLLISION_LIST_H_