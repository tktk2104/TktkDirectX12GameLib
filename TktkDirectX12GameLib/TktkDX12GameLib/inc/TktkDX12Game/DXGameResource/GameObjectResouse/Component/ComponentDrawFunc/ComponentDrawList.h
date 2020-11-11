#ifndef COMPONENT_DRAW_LIST_H_
#define COMPONENT_DRAW_LIST_H_

/* std::forward_list */
#include <forward_list>

/* std::multimap */
#include <map>

namespace tktk
{
	/* funcUseType */
	class ComponentBasePtr;
	struct ComponentDrawFuncVTable;

	/* class member */
	class ComponentDrawFuncRunner;

	// コンポーネントの描画処理を行うリスト
	class ComponentDrawList
	{
	public:

		ComponentDrawList();
		~ComponentDrawList();

	public:

		// 自身のコンテナに追加する
		void add(const ComponentBasePtr& componentPtr, ComponentDrawFuncVTable* vtablePtr);

		// 描画優先度順で「draw」関数を呼ぶ
		void runDrawFunc() const;

		// 前フレームに追加されたコンポーネントをメインリストに追加する
		void movePreFrameAddedNode();

		// 死亡フラグが立っているコンポーネントを削除する
		void removeDeadComponent();

	private:

		std::multimap<float, ComponentDrawFuncRunner>					m_drawList;
		std::forward_list<std::pair<float, ComponentDrawFuncRunner>>	m_nextFrameAddNodeList;
	};
}
#endif // !COMPONENT_DRAW_LIST_H_