#ifndef COMPONENT_DRAW_LIST_H_
#define COMPONENT_DRAW_LIST_H_

#include <forward_list>
#include <map>
#include <TktkTemplateMetaLib/HasFuncCheck/CreatedStruct/HasDrawChecker.h>
#include "ComponentDrawFuncRunner.h"

namespace tktk
{
	// 指定のクラスが変数がdraw関数を持っているか判定するテンプレートメタのエイリアステンプレート
	template <class ComponentType>
	using has_draw = std::enable_if_t<has_draw_checker<ComponentType*, void>::value>*;
	template <class ComponentType>
	using not_has_draw = std::enable_if_t<!has_draw_checker<ComponentType*, void>::value>*;

	// コンポーネントの描画処理を行うリスト
	class ComponentDrawList
	{
	public:

		ComponentDrawList() = default;

	public:

		// 描画優先度順で「draw」関数を呼ぶ
		void runDrawFunc();

		// 前フレームに追加されたコンポーネントをメインリストに追加する
		void movePreFrameAddedNode();

		// 死亡フラグが立っているコンポーネントを削除する
		void removeDeadComponent();

	public:

		// 引数のコンポーネントの型が「draw()」関数を持っていたら自身のコンテナに追加する
		template <class ComponentType, has_draw<ComponentType> = nullptr>
		void addComponent(const std::weak_ptr<ComponentType>& componentPtr);
		template <class ComponentType, not_has_draw<ComponentType> = nullptr>
		void addComponent(const std::weak_ptr<ComponentType>& componentPtr);

	private:

		std::multimap<float, ComponentDrawFuncRunner>					m_drawList;
		std::forward_list<std::pair<float, ComponentDrawFuncRunner>>	m_nextFrameAddNodeList;
	};
//┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//┃ここから下は関数の実装
//┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

	// 引数のコンポーネントの型が「draw()」関数を持っていたら自身のコンテナに追加する
	template<class ComponentType, has_draw<ComponentType>>
	inline void ComponentDrawList::addComponent(const std::weak_ptr<ComponentType>& componentPtr)
	{
		m_nextFrameAddNodeList.emplace_front(componentPtr.lock()->getDrawPriority(), componentPtr);
	}
	template<class ComponentType, not_has_draw<ComponentType>>
	inline void ComponentDrawList::addComponent(const std::weak_ptr<ComponentType>& componentPtr) {}
}
#endif // !COMPONENT_DRAW_LIST_H_