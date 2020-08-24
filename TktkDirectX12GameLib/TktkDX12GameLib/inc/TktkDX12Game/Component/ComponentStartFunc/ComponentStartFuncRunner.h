#ifndef COMPONENT_START_RUNNER_H_
#define COMPONENT_START_RUNNER_H_

#include <TktkTemplateMetaLib/HasFuncCheck/CreatedStruct/HasStartChecker.h>
#include "../ComponentBasePtr.h"

namespace tktk
{
	// コンポーネントの「start」関数を呼ぶためのクラス
	class ComponentStartFuncRunner
	{
	public:

		template <class ComponentType>
		ComponentStartFuncRunner(const std::weak_ptr<ComponentType>& componentPtr);

	public:

		// 「start」関数を呼ぶ
		void runStart();

		// コンポーネントの死亡フラグを取得する
		bool isDead() const;

	private:

		struct VTable
		{
			void(*runStart)(const ComponentBasePtr&);
		};

		template <class ComponentType>
		struct VTableInitializer
		{
			// 「start」関数を持っていたら呼ぶ処理を行う為の関数
			static void runStart(const ComponentBasePtr& runPtr);

			static VTable m_vtable;
		};

	private:

		bool				m_afterRun{ false };
		VTable*				m_vtablePtr;
		ComponentBasePtr	m_selfPtr;
	};
//┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//┃ここから下は関数の実装
//┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

	template<class ComponentType>
	inline ComponentStartFuncRunner::ComponentStartFuncRunner(const std::weak_ptr<ComponentType>& componentPtr)
		: m_vtablePtr(&VTableInitializer<ComponentType>::m_vtable)
		, m_selfPtr(componentPtr)
	{
	}

	template<class ComponentType>
	typename ComponentStartFuncRunner::VTable ComponentStartFuncRunner::VTableInitializer<ComponentType>::m_vtable =
	{
		&ComponentStartFuncRunner::VTableInitializer<ComponentType>::runStart
	};

	// 「start()」関数を持っていたら呼ぶ処理を行う為の関数
	template<class ComponentType>
	inline void ComponentStartFuncRunner::VTableInitializer<ComponentType>::runStart(const ComponentBasePtr& runPtr)
	{
		start_runner<void>::checkAndRun(runPtr.castPtr<ComponentType>());
	}
}
#endif // !COMPONENT_START_RUNNER_H_