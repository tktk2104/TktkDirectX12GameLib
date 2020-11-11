#ifndef COMPONENT_LIST_VTABLE_H_
#define COMPONENT_LIST_VTABLE_H_

/* std::shared_ptr */
#include <memory>

/* std::forward_list */
#include <forward_list>

/* update_runner<> */
#include <TktkTemplateMetaLib/HasFuncCheck/CreatedStruct/HasUpdateChecker.h>

/* afterCollide_runner<> */
#include <TktkTemplateMetaLib/HasFuncCheck/CreatedStruct/HasAfterCollideChecker.h>

/* onEnable_runner<> */
#include <TktkTemplateMetaLib/HasFuncCheck/CreatedStruct/HasOnEnableChecker.h>

/* onDisable_runner<> */
#include <TktkTemplateMetaLib/HasFuncCheck/CreatedStruct/HasOnDisableChecker.h>

/* onDestroy_runner<> */
#include <TktkTemplateMetaLib/HasFuncCheck/CreatedStruct/HasOnDestroyChecker.h>

/* funcUseType */
#include "../ComponentBase.h"

namespace tktk
{	
	// 自身が管理するコンポーネントの型情報を隠蔽するための関数ポインタ
	struct ComponentListVTable
	{
		void(*update)		(const std::forward_list<std::shared_ptr<ComponentBase>>&);
		void(*afterCollide)	(const std::forward_list<std::shared_ptr<ComponentBase>>&);
		void(*onEnable)		(const std::shared_ptr<ComponentBase>&);
		void(*onDisable)	(const std::shared_ptr<ComponentBase>&);
		void(*onDestroy)	(const std::shared_ptr<ComponentBase>&);
	};

	// 自身が管理するコンポーネントの型情報を隠蔽するための関数の実態が存在する所
	template <class ComponentType>
	struct ComponentListVTableInitializer
	{
		// 自身が管理するコンポーネントの型情報を隠蔽するための関数ポインタ
		static ComponentListVTable m_componentListVTable;

		// 引数リストのポインタの指す実態が「update」関数を持っていたら全ての要素でそれを実行する
		static void update(const std::forward_list<std::shared_ptr<ComponentBase>>& mainList)
		{
			for (const auto& node : mainList)
			{
				if (!node->isActive() || node->isDead()) continue;
				update_runner<void>::checkAndRun(std::dynamic_pointer_cast<ComponentType>(node));
			}
		}

		// 引数リストのポインタの指す実態が「afterCollide」関数を持っていたら全ての要素でそれを実行する
		static void afterCollide(const std::forward_list<std::shared_ptr<ComponentBase>>& mainList)
		{
			for (const auto& node : mainList)
			{
				if (!node->isActive() || node->isDead()) continue;
				afterCollide_runner<void>::checkAndRun(std::dynamic_pointer_cast<ComponentType>(node));
			}
		}

		// 「onEnable()」関数を持っていたら呼ぶ処理を行う為の関数
		static void onEnable(const std::shared_ptr<ComponentBase>& runPtr)	{ onEnable_runner<void>::checkAndRun(std::dynamic_pointer_cast<ComponentType>(runPtr)); }

		// 「onDisable()」関数を持っていたら呼ぶ処理を行う為の関数
		static void onDisable(const std::shared_ptr<ComponentBase>& runPtr) { onDisable_runner<void>::checkAndRun(std::dynamic_pointer_cast<ComponentType>(runPtr)); }

		// 「onDestroy()」関数を持っていたら呼ぶ処理を行う為の関数
		static void onDestroy(const std::shared_ptr<ComponentBase>& runPtr) { onDestroy_runner<void>::checkAndRun(std::dynamic_pointer_cast<ComponentType>(runPtr)); }
	};

	// 自身が管理するコンポーネントの型情報を隠蔽するための関数ポインタ
	template<class ComponentType>
	ComponentListVTable ComponentListVTableInitializer<ComponentType>::m_componentListVTable =
	{
		&ComponentListVTableInitializer<ComponentType>::update,
		&ComponentListVTableInitializer<ComponentType>::afterCollide,
		&ComponentListVTableInitializer<ComponentType>::onEnable,
		&ComponentListVTableInitializer<ComponentType>::onDisable,
		&ComponentListVTableInitializer<ComponentType>::onDestroy
	};
}
#endif // !COMPONENT_LIST_VTABLE_H_