#ifndef COMPONENT_DRAW_LIST_H_
#define COMPONENT_DRAW_LIST_H_

#include <memory>
#include <map>
#include <TktkTemplateMetaLib/HasFuncCheck/CreatedStruct/HasDrawChecker.h>
#include "ComponentDrawRunner.h"

namespace tktk
{
	// コンポーネントの描画処理を行うリスト
	class ComponentDrawList
	{
	public:

		ComponentDrawList() = default;

	public:

		// 引数のコンポーネントの型が「draw()」関数を持っていたら自身のコンテナに追加する
		template <class ComponentType, std::enable_if_t<has_draw_checker<ComponentType*, void>::value>* = nullptr>
		void addComponent(const std::weak_ptr<ComponentType>& componentPtr);
		template <class ComponentType, std::enable_if_t<!has_draw_checker<ComponentType*, void>::value>* = nullptr>
		void addComponent(const std::weak_ptr<ComponentType>& componentPtr);

		// 描画優先度順で「draw()」関数を呼ぶ
		void runDraw();

		// 前フレームに追加されたコンポーネントをメインリストに追加する
		void moveNewComponent();

		// 死亡フラグが立っているコンポーネントを削除する
		void removeDeadComponent();

	private:

		std::multimap<float, ComponentDrawRunner> m_drawList;
		std::multimap<float, ComponentDrawRunner> m_newComponentList;
	};
//┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//┃ここから下は関数の実装
//┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

	// 引数のコンポーネントの型が「draw()」関数を持っていたら自身のコンテナに追加する
	template<class ComponentType, std::enable_if_t<has_draw_checker<ComponentType*, void>::value>*>
	inline void ComponentDrawList::addComponent(const std::weak_ptr<ComponentType>& componentPtr)
	{
		m_newComponentList.emplace(componentPtr.lock()->getDrawPriority(), componentPtr);
	}
	template<class ComponentType, std::enable_if_t<!has_draw_checker<ComponentType*, void>::value>*>
	inline void ComponentDrawList::addComponent(const std::weak_ptr<ComponentType>& componentPtr) {}
}
#endif // !COMPONENT_DRAW_LIST_H_