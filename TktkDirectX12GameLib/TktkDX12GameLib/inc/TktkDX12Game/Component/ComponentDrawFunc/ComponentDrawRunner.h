#ifndef COMPONENT_DRAW_RUNNER_H_
#define COMPONENT_DRAW_RUNNER_H_

#include <memory>
#include <TktkTemplateMetaLib/HasFuncCheck/CreatedStruct/HasDrawChecker.h>

namespace tktk
{
	class ComponentBase;

	// コンポーネントの描画関数を呼ぶためのクラス
	class ComponentDrawRunner
	{
	public:

		template <class ComponentType>
		ComponentDrawRunner(const std::weak_ptr<ComponentType>& componentPtr);

	public:

		// 描画処理を行う
		void runDraw();

		// コンポーネントが死亡しているかを取得する
		bool isDead() const;

	private:

		struct VTable
		{
			void(*runDraw)(const std::weak_ptr<ComponentBase>&);
		};

		template <class ComponentType>
		struct VTableInitializer
		{
			// 「draw()」関数を持っていたら呼ぶ処理を行う為の関数
			static void runDraw(const std::weak_ptr<ComponentBase>& runPtr);

			static VTable m_vtable;
		};

	private:

		VTable*							m_vtablePtr;
		std::weak_ptr<ComponentBase>	m_componentPtr;
	};
//┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//┃ここから下は関数の実装
//┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

	template<class ComponentType>
	inline ComponentDrawRunner::ComponentDrawRunner(const std::weak_ptr<ComponentType>& componentPtr)
		: m_vtablePtr(&VTableInitializer<ComponentType>::m_vtable)
		, m_componentPtr(componentPtr)
	{
	}

	template<class ComponentType>
	typename ComponentDrawRunner::VTable ComponentDrawRunner::VTableInitializer<ComponentType>::m_vtable =
	{
		&ComponentDrawRunner::VTableInitializer<ComponentType>::runDraw,
	};

	// 「draw()」関数を持っていたら呼ぶ処理を行う為の関数
	template<class ComponentType>
	inline void ComponentDrawRunner::VTableInitializer<ComponentType>::runDraw(const std::weak_ptr<ComponentBase>& runPtr)
	{
		draw_runner<void>::checkAndRun(std::dynamic_pointer_cast<ComponentType>(runPtr.lock()));
	}
}
#endif // !COMPONENT_DRAW_RUNNER_H_