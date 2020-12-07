#ifndef SCENE_V_TABLE_H_
#define SCENE_V_TABLE_H_

/* std::weak_ptr */
#include <memory>

/* start_runner<> */
#include <TktkTemplateMetaLib/HasFuncCheck/CreatedStruct/HasStartChecker.h>

/* update_runner<> */
#include <TktkTemplateMetaLib/HasFuncCheck/CreatedStruct/HasUpdateChecker.h>

/* end_runner<> */
#include <TktkTemplateMetaLib/HasFuncCheck/CreatedStruct/HasEndChecker.h>

namespace tktk
{
	class SceneBase;

	// シーンクラスの関数実行クラス
	struct SceneVTable
	{
		void (*start)	(const std::weak_ptr<SceneBase>&);
		void (*update)	(const std::weak_ptr<SceneBase>&);
		void (*end)		(const std::weak_ptr<SceneBase>&);
	};

	// 「SceneVTable」を作るために必要な静的関数ポインタ
	template <class SceneType>
	struct SceneVTableInitializer
	{
		// テンプレートクラスの「start, update, end」関数を持っていたら実行する関数のポインタを保持する構造体
		static SceneVTable m_vtable;

		// 引数のポインタの指す実態が「start」関数を持っていたら実行する
		static void start(const std::weak_ptr<SceneBase>& self)
		{
			if (self.expired()) return;
			start_runner<void>::checkAndRun(std::dynamic_pointer_cast<SceneType>(self.lock()));
		}

		// 引数のポインタの指す実態が「update」関数を持っていたら実行する
		static void update(const std::weak_ptr<SceneBase>& self)
		{
			if (self.expired()) return;
			update_runner<void>::checkAndRun(std::dynamic_pointer_cast<SceneType>(self.lock()));
		}

		// 引数のポインタの指す実態が「end」関数を持っていたら実行する
		static void end(const std::weak_ptr<SceneBase>& self)
		{
			if (self.expired()) return;
			end_runner<void>::checkAndRun(std::dynamic_pointer_cast<SceneType>(self.lock()));
		}
	};

	// テンプレートクラスの「start, update, end」関数を持っていたら実行する関数のポインタを保持する構造体
	template <class SceneType>
	SceneVTable SceneVTableInitializer<SceneType>::m_vtable =
	{
		&SceneVTableInitializer<SceneType>::start,
		&SceneVTableInitializer<SceneType>::update,
		&SceneVTableInitializer<SceneType>::end
	};
}
#endif // !SCENE_V_TABLE_H_