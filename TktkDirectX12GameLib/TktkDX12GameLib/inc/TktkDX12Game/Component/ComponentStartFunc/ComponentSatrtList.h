#ifndef COMPONENT_SATRT_LIST_H_
#define COMPONENT_SATRT_LIST_H_

#include <memory>
#include <forward_list>
#include <TktkTemplateMetaLib/HasFuncCheck/CreatedStruct/HasStartChecker.h>
#include "ComponentStartRunner.h"

namespace tktk
{
	// コンポーネントの「start」関数を実行するリスト
	class ComponentSatrtList
	{
	public:

		ComponentSatrtList() = default;

	public:

		// 引数のコンポーネントの型が「start()」関数を持っていたら自身のコンテナに追加する
		template <class ComponentType, std::enable_if_t<has_start_checker<ComponentType*, void>::value>* = nullptr>
		void addComponent(const std::weak_ptr<ComponentType>& componentPtr);
		template <class ComponentType, std::enable_if_t<!has_start_checker<ComponentType*, void>::value>* = nullptr>
		void addComponent(const std::weak_ptr<ComponentType>& componentPtr);

		// 「start()」関数を呼ぶ
		void runStart();

		// 前フレームに追加されたコンポーネントをメインリストに追加する
		void moveNewComponent();

		// 既に「start()」関数が呼ばれたか、死亡フラグが立っているコンポーネントを削除する
		void removeDeadComponent();

	private:

		std::forward_list<ComponentStartRunner> m_startList;
		std::forward_list<ComponentStartRunner> m_newComponentList;
	};
//┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//┃ここから下は関数の実装
//┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

	// 引数のコンポーネントの型が「start()」関数を持っていたら自身のコンテナに追加する
	template<class ComponentType, std::enable_if_t<has_start_checker<ComponentType*, void>::value>*>
	inline void ComponentSatrtList::addComponent(const std::weak_ptr<ComponentType>& componentPtr)
	{
		m_newComponentList.emplace_front(componentPtr);
	}
	template<class ComponentType, std::enable_if_t<!has_start_checker<ComponentType*, void>::value>*>
	inline void ComponentSatrtList::addComponent(const std::weak_ptr<ComponentType>& componentPtr) {}
}
#endif // !COMPONENT_SATRT_LIST_H_