#ifndef COMPONENT_COLLISION_FUNC_RUNNER_H_
#define COMPONENT_COLLISION_FUNC_RUNNER_H_

#include <forward_list>
#include <TktkTemplateMetaLib/HasFuncCheck/CreatedStruct/HasIsCollideChecker.h>
#include "../../GameObject/GameObjectPtr.h"
#include "../ComponentBasePtr.h"

namespace tktk
{
	// コンポーネントの衝突判定関数を呼ぶためのクラス
	class ComponentCollisionFuncRunner
	{
	public:

		template <class ComponentType>
		ComponentCollisionFuncRunner(const std::weak_ptr<ComponentType>& componentPtr);

	public:

		// 前フレームで衝突したオブジェクトを管理するリストを更新する
		void updateHitObjectList();

		// 衝突判定処理を行う
		void runCollideFunc(const ComponentCollisionFuncRunner& other);

		// コンポーネントが死亡しているかを取得する
		bool isDead() const;

	private:

		struct VTable
		{
			bool(*runIsCollide)			(const ComponentBasePtr&, const ComponentBasePtr&);
		};

		template <class ComponentType>
		struct VTableInitializer
		{
			// 衝突判定関数を持っていたら呼ぶ処理
			static bool runIsCollide		(const ComponentBasePtr& self, const ComponentBasePtr& other);

			static VTable m_vtable;
		};

	private:

		// 衝突相手の情報
		struct HitObject
		{
			HitObject(VTable* vtablePtr, ComponentBasePtr selfPtr);

			VTable*				vtablePtr;
			ComponentBasePtr	selfPtr;
		};

	private:

		VTable*				m_vtablePtr;
		ComponentBasePtr	m_selfPtr;

		// 現在のフレームの衝突相手情報
		std::forward_list<HitObject> m_curHitObjectList;

		// １つ前のフレームの衝突相手情報
		std::forward_list<HitObject> m_preHitObjectList;
	};

//┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//┃ここから下は関数の実装
//┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

	template<class ComponentType>
	inline ComponentCollisionFuncRunner::ComponentCollisionFuncRunner(const std::weak_ptr<ComponentType>& componentPtr)
		: m_vtablePtr(&VTableInitializer<ComponentType>::m_vtable)
		, m_selfPtr(componentPtr)
	{
	}

	template<class ComponentType>
	typename ComponentCollisionFuncRunner::VTable ComponentCollisionFuncRunner::VTableInitializer<ComponentType>::m_vtable =
	{
		&ComponentCollisionFuncRunner::VTableInitializer<ComponentType>::runIsCollide
	};

	// 衝突判定関数を持っていたら呼ぶ処理
	template<class ComponentType>
	inline bool ComponentCollisionFuncRunner::VTableInitializer<ComponentType>::runIsCollide(const ComponentBasePtr& self, const ComponentBasePtr& other)
	{
		return isCollide_runner<bool, const ComponentBasePtr&>::checkAndRun(self.castPtr<ComponentType>(), false, other);
	}
}
#endif // !COMPONENT_COLLISION_FUNC_RUNNER_H_