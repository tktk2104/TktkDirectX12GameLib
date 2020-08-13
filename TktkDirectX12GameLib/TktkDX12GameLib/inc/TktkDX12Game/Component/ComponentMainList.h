#ifndef COMPONENT_MAIN_LIST_H_
#define COMPONENT_MAIN_LIST_H_

#include <memory>
#include <utility>
#include <forward_list>
#include <TktkTemplateMetaLib/HasFuncCheck/CreatedStruct/HasAwakeChecker.h>
#include <TktkTemplateMetaLib/HasFuncCheck/CreatedStruct/HasOnEnableChecker.h>
#include <TktkTemplateMetaLib/HasFuncCheck/CreatedStruct/HasOnDisableChecker.h>
#include <TktkTemplateMetaLib/HasFuncCheck/CreatedStruct/HasUpdateChecker.h>
#include <TktkTemplateMetaLib/HasFuncCheck/CreatedStruct/HasAfterCollideChecker.h>
#include <TktkTemplateMetaLib/HasFuncCheck/CreatedStruct/HasOnDestroyChecker.h>

namespace tktk
{
	class ComponentBase;

	// １種類のコンポーネントを管理するリストクラス
	class ComponentMainList
	{
	public:

		// このクラスで管理するコンポーネントの型のポインタを引数に渡す
		// ※ポインタの型情報だけあれば良いのでNULLポインタで良い
		template<class ComponentType>
		ComponentMainList(ComponentType* rawPtr);

	public:

		// テンプレート引数の型のコンポーネントを引数の値を使って作る
		// ※コンストラクタで指定した型でないとビルド不可
		template <class ComponentType, class... Args>
		std::weak_ptr<ComponentType> createComponent(Args&&... args);

		// 自身が管理するコンポーネントを巡回し、アクティブフラグが前フレームと変わっていたら「onEnable()」もしくは「onDisable()」関数の実行を試みる
		void activeChangeCheck();

		// 自身が管理するコンポーネントの型が「update()」関数を持っていたらそれらを全て実行する
		void runUpdate();

		// 自身が管理するコンポーネントの型が「afterCollide」関数を持っていたらそれらを全て実行する
		void runAfterCollide();

		// 前フレームに追加されたコンポーネントをメインリストに追加する
		void moveNewComponent();

		// 死亡フラグが立っているコンポーネントを削除する
		void removeDeadComponent();

	private:

		// 自身が管理するコンポーネントの型情報を隠蔽するための関数ポインタ
		struct VTable
		{
			void(*runUpdate)(const std::forward_list<std::shared_ptr<ComponentBase>>&);
			void(*runAfterCollide)(const std::forward_list<std::shared_ptr<ComponentBase>>&);
			void(*runOnEnable)(const std::shared_ptr<ComponentBase>&);
			void(*runOnDisable)(const std::shared_ptr<ComponentBase>&);
			void(*runOnDestroy)(const std::shared_ptr<ComponentBase>&);
		};

		// 自身が管理するコンポーネントの型情報を隠蔽するための関数の実態が存在する所
		template <class ComponentType>
		struct VTableInitializer
		{
			// 「update()」関数を持っていたら呼ぶ処理を行う為の関数達
			static void runUpdate(const std::forward_list<std::shared_ptr<ComponentBase>>& mainList);
			template <class U, std::enable_if_t<has_update_checker<U*, void>::value>* = nullptr>
			static void checkAndRunUpdate(const std::forward_list<std::shared_ptr<ComponentBase>>& mainList);
			template <class U, std::enable_if_t<!has_update_checker<U*, void>::value>* = nullptr>
			static void checkAndRunUpdate(const std::forward_list<std::shared_ptr<ComponentBase>>& mainList);

			// 「afterCollide()」関数を持っていたら呼ぶ処理を行う為の関数達
			static void runAfterCollide(const std::forward_list<std::shared_ptr<ComponentBase>>& mainList);
			template <class U, std::enable_if_t<has_afterCollide_checker<U*, void>::value>* = nullptr>
			static void checkAndRunAfterCollide(const std::forward_list<std::shared_ptr<ComponentBase>>& mainList);
			template <class U, std::enable_if_t<!has_afterCollide_checker<U*, void>::value>* = nullptr>
			static void checkAndRunAfterCollide(const std::forward_list<std::shared_ptr<ComponentBase>>& mainList);

			// 「onEnable()」関数を持っていたら呼ぶ処理を行う為の関数
			static void runOnEnable(const std::shared_ptr<ComponentBase>& runPtr);

			// 「onDisable()」関数を持っていたら呼ぶ処理を行う為の関数
			static void runOnDisable(const std::shared_ptr<ComponentBase>& runPtr);

			// 「onDestroy()」関数を持っていたら呼ぶ処理を行う為の関数
			static void runOnDestroy(const std::shared_ptr<ComponentBase>& runPtr);

			static VTable m_vtable;
		};

	private:

		VTable*												m_vtablePtr;
		std::forward_list<std::shared_ptr<ComponentBase>>	m_mainList;
		std::forward_list<std::shared_ptr<ComponentBase>>	m_newComponentList;
	};
//┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//┃ここから下は関数の実装
//┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

	// このクラスで管理するコンポーネントの型のポインタを引数に渡す
	// ※ポインタの型情報だけあれば良いのでNULLポインタで良い
	template<class ComponentType>
	inline ComponentMainList::ComponentMainList(ComponentType* rawPtr)
		: m_vtablePtr(&VTableInitializer<ComponentType>::m_vtable)
	{
	}

	// テンプレート引数の型のコンポーネントを引数の値を使って作る
	// ※コンストラクタで指定した型でないとビルド不可
	template<class ComponentType, class ...Args>
	inline std::weak_ptr<ComponentType> ComponentMainList::createComponent(Args&& ...args)
	{
		auto createdComponent = std::make_shared<ComponentType>(std::forward<Args>(args)...);
		awake_runner<void>::checkAndRun(createdComponent);
		m_newComponentList.push_front(createdComponent);
		return createdComponent;
	}

	template<class ComponentType>
	typename ComponentMainList::VTable ComponentMainList::VTableInitializer<ComponentType>::m_vtable =
	{
		&ComponentMainList::VTableInitializer<ComponentType>::runUpdate,
		&ComponentMainList::VTableInitializer<ComponentType>::runAfterCollide,
		&ComponentMainList::VTableInitializer<ComponentType>::runOnEnable,
		&ComponentMainList::VTableInitializer<ComponentType>::runOnDisable,
		&ComponentMainList::VTableInitializer<ComponentType>::runOnDestroy
	};

	// 「update()」関数を持っていたら呼ぶ処理を行う為の関数達
	template<class ComponentType>
	inline void ComponentMainList::VTableInitializer<ComponentType>::runUpdate(const std::forward_list<std::shared_ptr<ComponentBase>>& mainList)
	{
		checkAndRunUpdate<ComponentType>(mainList);
	}
	template<class ComponentType>
	template<class U, std::enable_if_t<has_update_checker<U*, void>::value>*>
	inline void ComponentMainList::VTableInitializer<ComponentType>::checkAndRunUpdate(const std::forward_list<std::shared_ptr<ComponentBase>>& mainList)
	{
		for (const auto& node : mainList)
		{
			if (!node->isActive()) continue;
			std::dynamic_pointer_cast<U>(node)->update();
		}
	}
	template<class ComponentType>
	template<class U, std::enable_if_t<!has_update_checker<U*, void>::value>*>
	inline void ComponentMainList::VTableInitializer<ComponentType>::checkAndRunUpdate(const std::forward_list<std::shared_ptr<ComponentBase>>& mainList) {}

	// 「afterCollide()」関数を持っていたら呼ぶ処理を行う為の関数達
	template<class ComponentType>
	inline void ComponentMainList::VTableInitializer<ComponentType>::runAfterCollide(const std::forward_list<std::shared_ptr<ComponentBase>>& mainList)
	{
		checkAndRunAfterCollide<ComponentType>(mainList);
	}
	template<class ComponentType>
	template<class U, std::enable_if_t<has_afterCollide_checker<U*, void>::value>*>
	inline void ComponentMainList::VTableInitializer<ComponentType>::checkAndRunAfterCollide(const std::forward_list<std::shared_ptr<ComponentBase>>& mainList)
	{
		for (const auto& node : mainList)
		{
			if (!node->isActive()) continue;
			std::dynamic_pointer_cast<U>(node)->afterCollide();
		}
	}
	template<class ComponentType>
	template<class U, std::enable_if_t<!has_afterCollide_checker<U*, void>::value>*>
	inline void ComponentMainList::VTableInitializer<ComponentType>::checkAndRunAfterCollide(const std::forward_list<std::shared_ptr<ComponentBase>>& mainList) {}

	// 「onEnable()」関数を持っていたら呼ぶ処理を行う為の関数
	template<class ComponentType>
	inline void ComponentMainList::VTableInitializer<ComponentType>::runOnEnable(const std::shared_ptr<ComponentBase>& runPtr)
	{
		onEnable_runner<void>::checkAndRun(std::dynamic_pointer_cast<ComponentType>(runPtr));
	}

	// 「onDisable()」関数を持っていたら呼ぶ処理を行う為の関数
	template<class ComponentType>
	inline void ComponentMainList::VTableInitializer<ComponentType>::runOnDisable(const std::shared_ptr<ComponentBase>& runPtr)
	{
		onDisable_runner<void>::checkAndRun(std::dynamic_pointer_cast<ComponentType>(runPtr));
	}

	// 「onDestroy()」関数を持っていたら呼ぶ処理を行う為の関数
	template<class ComponentType>
	inline void ComponentMainList::VTableInitializer<ComponentType>::runOnDestroy(const std::shared_ptr<ComponentBase>& runPtr)
	{
		onDestroy_runner<void>::checkAndRun(std::dynamic_pointer_cast<ComponentType>(runPtr));
	}
}
#endif // !COMPONENT_MAIN_LIST_H_