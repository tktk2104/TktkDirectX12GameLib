#ifndef COMPONENT_SATRT_LIST_H_
#define COMPONENT_SATRT_LIST_H_

/* std::forward_list */
#include <forward_list>

namespace tktk
{
	class ComponentStartFuncRunner;
	class ComponentBasePtr;
	struct ComponentStartFuncVTable;

	// コンポーネントの「start」関数を実行するリスト
	class ComponentStartList
	{
	public:

		ComponentStartList();
		~ComponentStartList();

	public:

		// 自身のコンテナに追加する
		void add(const ComponentBasePtr& componentPtr, ComponentStartFuncVTable* vtablePtr);

		// 「start」関数を呼ぶ
		void runStartFunc();

		// 前フレームに追加されたコンポーネントをメインリストに追加する
		void movePreFrameAddedNode();

		// 既に「start」関数が呼ばれたか、死亡フラグが立っているコンポーネントを削除する
		void removeDeadComponent();

	private:

		std::forward_list<ComponentStartFuncRunner> m_startList;
		std::forward_list<ComponentStartFuncRunner> m_nextFrameAddNodeList;
	};
}
#endif // !COMPONENT_SATRT_LIST_H_