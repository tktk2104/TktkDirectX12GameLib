#ifndef SCENE_V_TABLE_H_
#define SCENE_V_TABLE_H_

#include <memory>
#include <TktkTemplateMetaLib/HasFuncCheck/CreatedStruct/HasStartChecker.h>
#include <TktkTemplateMetaLib/HasFuncCheck/CreatedStruct/HasEndChecker.h>
#include <TktkTemplateMetaLib/HasFuncCheck/CreatedStruct/HasUpdateChecker.h>
#include "SceneBase.h"

namespace tktk
{
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
		static SceneVTable m_vtable;

		static void start	(const std::weak_ptr<SceneBase>& self);
		static void update	(const std::weak_ptr<SceneBase>& self);
		static void end		(const std::weak_ptr<SceneBase>& self);
	};
//┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//┃ここから下は関数の実装
//┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

	template <class SceneType>
	SceneVTable SceneVTableInitializer<SceneType>::m_vtable =
	{
		&SceneVTableInitializer<SceneType>::start,
		&SceneVTableInitializer<SceneType>::update,
		&SceneVTableInitializer<SceneType>::end
	};

	template<class SceneType>
	inline void SceneVTableInitializer<SceneType>::start(const std::weak_ptr<SceneBase>& self)
	{
		if (self.expired()) return;

		start_runner<void>::checkAndRun(std::dynamic_pointer_cast<SceneType>(self.lock()));
	}

	template<class SceneType>
	inline void SceneVTableInitializer<SceneType>::update(const std::weak_ptr<SceneBase>& self)
	{
		if (self.expired()) return;

		update_runner<void>::checkAndRun(std::dynamic_pointer_cast<SceneType>(self.lock()));
	}

	template<class SceneType>
	inline void SceneVTableInitializer<SceneType>::end(const std::weak_ptr<SceneBase>& self)
	{
		if (self.expired()) return;

		end_runner<void>::checkAndRun(std::dynamic_pointer_cast<SceneType>(self.lock()));
	}
}
#endif // !SCENE_V_TABLE_H_