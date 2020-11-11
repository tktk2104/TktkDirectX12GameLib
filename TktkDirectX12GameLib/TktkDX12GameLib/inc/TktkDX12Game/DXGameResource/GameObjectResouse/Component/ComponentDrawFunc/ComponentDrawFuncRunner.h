#ifndef COMPONENT_DRAW_RUNNER_H_
#define COMPONENT_DRAW_RUNNER_H_

/* class member */
#include "../ComponentBasePtr.h"

namespace tktk
{
	struct ComponentDrawFuncVTable;

	// コンポーネントの描画関数を呼ぶためのクラス
	class ComponentDrawFuncRunner
	{
	public:

		ComponentDrawFuncRunner(const ComponentBasePtr& componentPtr, ComponentDrawFuncVTable* vtablePtr);

	public:

		// 描画処理を行う
		void runDrawFunc() const;

		// コンポーネントが死亡しているかを取得する
		bool isDead() const;

	private:

		ComponentDrawFuncVTable*	m_vtablePtr;
		ComponentBasePtr			m_selfPtr;
	};
}
#endif // !COMPONENT_DRAW_RUNNER_H_