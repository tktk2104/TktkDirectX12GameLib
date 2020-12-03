#ifndef COMPONENT_TYPE_LIST_H_
#define COMPONENT_TYPE_LIST_H_

/* std::shared_ptr */
#include <memory>

/* std::forward_list */
#include <forward_list>

namespace tktk
{
	struct ComponentListVTable;
	class ComponentBase;

	// １種類のコンポーネントを管理するリストクラス
	class ComponentTypeList
	{
	public:

		explicit ComponentTypeList(ComponentListVTable* vtablePtr);

	public:

		// コンポーネントを追加する
		void addComponent(const std::shared_ptr<ComponentBase>& componentPtr);

		// 自身が管理するコンポーネントを巡回し、アクティブフラグが前フレームと変わっていたら「onEnable()」もしくは「onDisable()」関数の実行を試みる
		void activeChangeCheck();

		// 自身が管理するコンポーネントの型が「update()」関数を持っていたらそれらを全て実行する
		void runUpdate();

		// 自身が管理するコンポーネントの型が「beforeCollide」関数を持っていたらそれらを全て実行する
		void runBeforeCollide();

		// 自身が管理するコンポーネントの型が「afterCollide」関数を持っていたらそれらを全て実行する
		void runAfterCollide();

		// 前フレームに追加されたコンポーネントをメインリストに追加する
		void moveNewComponent();

		// 死亡フラグが立っているコンポーネントを削除する
		void removeDeadComponent();

	private:

		ComponentListVTable*								m_vtablePtr;
		std::forward_list<std::shared_ptr<ComponentBase>>	m_mainList;
		std::forward_list<std::shared_ptr<ComponentBase>>	m_newComponentList;
	};
}
#endif // !COMPONENT_TYPE_LIST_H_