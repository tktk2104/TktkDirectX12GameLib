#ifndef COMPONENT_START_RUNNER_H_
#define COMPONENT_START_RUNNER_H_

/* class member */
#include "../ComponentBasePtr.h"

namespace tktk
{
	struct ComponentStartFuncVTable;

	// コンポーネントの「start」関数を呼ぶためのクラス
	class ComponentStartFuncRunner
	{
	public:

		ComponentStartFuncRunner(const ComponentBasePtr& componentPtr, ComponentStartFuncVTable* vtablePtr);

	public:

		// 「start」関数を呼ぶ
		void runStart();

		// コンポーネントの死亡フラグを取得する
		bool isDead() const;

	private:

		bool						m_afterRun{ false };
		ComponentStartFuncVTable*	m_vtablePtr;
		ComponentBasePtr			m_selfPtr;
	};
}
#endif // !COMPONENT_START_RUNNER_H_