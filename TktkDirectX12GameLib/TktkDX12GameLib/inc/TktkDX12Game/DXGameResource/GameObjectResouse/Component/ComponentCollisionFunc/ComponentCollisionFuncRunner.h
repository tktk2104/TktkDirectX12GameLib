#ifndef COMPONENT_COLLISION_FUNC_RUNNER_H_
#define COMPONENT_COLLISION_FUNC_RUNNER_H_

/* std::forward_list */
#include <forward_list>

/* funcUseType */
#include "../ComponentBasePtr.h"

namespace tktk
{
	struct ComponentCollisionFuncVTable;

	// コンポーネントの衝突判定関数を呼ぶためのクラス
	class ComponentCollisionFuncRunner
	{
	public:

		ComponentCollisionFuncRunner(const ComponentBasePtr& componentPtr, ComponentCollisionFuncVTable* vtablePtr);

	public:

		// 前フレームで衝突したオブジェクトを管理するリストを更新する
		void updateHitObjectList();

		// 衝突判定処理を行う
		void runCollideFunc(const ComponentCollisionFuncRunner& other);

		// コンポーネントが死亡しているかを取得する
		bool isDead() const;

	private:

		// 衝突相手の情報
		struct HitObject
		{
			HitObject(ComponentCollisionFuncVTable* vtablePtr, ComponentBasePtr selfPtr)
				: vtablePtr(vtablePtr)
				, selfPtr(selfPtr) {}

			ComponentCollisionFuncVTable*	vtablePtr;
			ComponentBasePtr				selfPtr;
		};

	private:

		ComponentCollisionFuncVTable*	m_vtablePtr;
		ComponentBasePtr				m_selfPtr;

		// 現在のフレームの衝突相手情報
		std::forward_list<HitObject> m_curHitObjectList;

		// １つ前のフレームの衝突相手情報
		std::forward_list<HitObject> m_preHitObjectList;
	};
}
#endif // !COMPONENT_COLLISION_FUNC_RUNNER_H_