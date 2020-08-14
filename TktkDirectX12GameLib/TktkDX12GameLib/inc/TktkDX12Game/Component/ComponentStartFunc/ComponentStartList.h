#ifndef COMPONENT_SATRT_LIST_H_
#define COMPONENT_SATRT_LIST_H_

#include <forward_list>
#include <TktkTemplateMetaLib/HasFuncCheck/CreatedStruct/HasStartChecker.h>
#include "ComponentStartFuncRunner.h"

namespace tktk
{
	// 指定のクラスが変数がstart関数を持っているか判定するテンプレートメタのエイリアステンプレート
	template <class ComponentType>
	using has_start = std::enable_if_t<has_start_checker<ComponentType*, void>::value>*;
	template <class ComponentType>
	using not_has_start = std::enable_if_t<!has_start_checker<ComponentType*, void>::value>*;

	// コンポーネントの「start」関数を実行するリスト
	class ComponentStartList
	{
	public:

		ComponentStartList() = default;

	public:

		// 引数のコンポーネントの型が「start」関数を持っていたら自身のコンテナに追加する
		template <class ComponentType, has_start<ComponentType> = nullptr>
		void add(const std::weak_ptr<ComponentType>& componentPtr);
		template <class ComponentType, not_has_start<ComponentType> = nullptr>
		void add(const std::weak_ptr<ComponentType>& componentPtr);

		// 「start()」関数を呼ぶ
		void runStartFunc();

		// 前フレームに追加されたコンポーネントをメインリストに追加する
		void movePreFrameAddedNode();

		// 既に「start」関数が呼ばれたか、死亡フラグが立っているコンポーネントを削除する
		void removeDeadComponent();

	private:

		std::forward_list<ComponentStartFuncRunner> m_startList;
		std::forward_list<ComponentStartFuncRunner> m_nextFrameAddNodeList;
	};
//┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//┃ここから下は関数の実装
//┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

	// 引数のコンポーネントの型が「start()」関数を持っていたら自身のコンテナに追加する
	template<class ComponentType, has_start<ComponentType>>
	inline void ComponentStartList::add(const std::weak_ptr<ComponentType>& componentPtr)
	{
		m_nextFrameAddNodeList.emplace_front(componentPtr);
	}
	template<class ComponentType, not_has_start<ComponentType>>
	inline void ComponentStartList::add(const std::weak_ptr<ComponentType>& componentPtr) {}
}
#endif // !COMPONENT_SATRT_LIST_H_