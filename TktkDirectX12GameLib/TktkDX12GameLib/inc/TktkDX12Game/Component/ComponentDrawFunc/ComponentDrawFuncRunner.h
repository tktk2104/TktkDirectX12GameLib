#ifndef COMPONENT_DRAW_RUNNER_H_
#define COMPONENT_DRAW_RUNNER_H_

#include <TktkTemplateMetaLib/HasFuncCheck/CreatedStruct/HasDrawChecker.h>
#include "../ComponentBasePtr.h"

namespace tktk
{
	// コンポーネントの描画関数を呼ぶためのクラス
	class ComponentDrawFuncRunner
	{
	public:

		template <class ComponentType>
		ComponentDrawFuncRunner(const std::weak_ptr<ComponentType>& componentPtr);

	public:

		// 描画処理を行う
		void runDrawFunc() const;

		// コンポーネントが死亡しているかを取得する
		bool isDead() const;

	private:

		struct VTable
		{
			void(*runDraw)	(const ComponentBasePtr&);
		};

		template <class ComponentType>
		struct VTableInitializer
		{
			// 「draw」関数を持っていたら呼ぶ処理を行う為の関数
			static void runDraw(const ComponentBasePtr& runPtr);

			static VTable m_vtable;
		};

	private:

		VTable*				m_vtablePtr;
		ComponentBasePtr	m_selfPtr;
	};
//┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//┃ここから下は関数の実装
//┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

	template<class ComponentType>
	inline ComponentDrawFuncRunner::ComponentDrawFuncRunner(const std::weak_ptr<ComponentType>& componentPtr)
		: m_vtablePtr(&VTableInitializer<ComponentType>::m_vtable)
		, m_selfPtr(componentPtr)
	{
	}

	template<class ComponentType>
	typename ComponentDrawFuncRunner::VTable ComponentDrawFuncRunner::VTableInitializer<ComponentType>::m_vtable =
	{
		&ComponentDrawFuncRunner::VTableInitializer<ComponentType>::runDraw,
	};

	// 「draw」関数を持っていたら呼ぶ処理
	template<class ComponentType>
	inline void ComponentDrawFuncRunner::VTableInitializer<ComponentType>::runDraw(const ComponentBasePtr& runPtr)
	{
		draw_runner<void>::checkAndRun(runPtr.castPtr<ComponentType>());
	}
}
#endif // !COMPONENT_DRAW_RUNNER_H_