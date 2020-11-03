#ifndef COMPONENT_GAME_OBJECT_FUNC_RUNNER_H_
#define COMPONENT_GAME_OBJECT_FUNC_RUNNER_H_

#include <TktkTemplateMetaLib/HasFuncCheck/CreatedStruct/HasHandleMessageChecker.h>
#include <TktkTemplateMetaLib/HasFuncCheck/CreatedStruct/HasAfterChangeParentChecker.h>
#include <TktkTemplateMetaLib/HasFuncCheck/CreatedStruct/HasOnCollisionEnterChecker.h>
#include <TktkTemplateMetaLib/HasFuncCheck/CreatedStruct/HasOnCollisionStayChecker.h>
#include <TktkTemplateMetaLib/HasFuncCheck/CreatedStruct/HasOnCollisionExitChecker.h>
#include "../../GameObject/GameObjectPtr.h"
#include "../ComponentBasePtr.h"
#include "../../EventMessage/MessageTypeCarrier.h"
#include "../../EventMessage/MessageAttachment.h"

namespace tktk
{
	// ゲームオブジェクトが使用するコンポーネントの関数を実行するクラス
	class ComponentGameObjectFuncRunner
	{
	public:

		template <class ComponentType>
		ComponentGameObjectFuncRunner(const std::weak_ptr<ComponentType>& componentPtr);

	public:

		// 型情報を隠蔽したコンポーネントポインタを取得する
		const ComponentBasePtr& getComponentBasePtr() const;

		// メッセージ取得関数を呼ぶ
		void runHandleMessage(MessageTypeCarrier type, const MessageAttachment& attachment) const;

		// コンポーネントの親要素が変わった時関数を呼ぶ
		void runAfterChangeParent(const GameObjectPtr& beforParent) const;

		// コンポーネントの衝突開始関数を呼ぶ
		void runOnCollisionEnter(const GameObjectPtr& other) const;

		// コンポーネントの衝突中関数を呼ぶ
		void runOnCollisionStay(const GameObjectPtr& other) const;

		// コンポーネントの衝突終了関数を呼ぶ
		void runOnCollisionExit(const GameObjectPtr& other) const;

		// コンポーネントの死亡フラグを取得する
		bool isDead() const;

		// コンポーネントを殺す
		void destroy() const;

	private:

		struct VTable
		{
			void(*runHandleMessage)		(const ComponentBasePtr&, MessageTypeCarrier, const MessageAttachment&);
			void(*runAfterChangeParent)	(const ComponentBasePtr&, const GameObjectPtr&);
			void(*runOnCollisionEnter)	(const ComponentBasePtr&, const GameObjectPtr&);
			void(*runOnCollisionStay)	(const ComponentBasePtr&, const GameObjectPtr&);
			void(*runOnCollisionExit)	(const ComponentBasePtr&, const GameObjectPtr&);
		};

		template <class ComponentType>
		struct VTableInitializer
		{
			// メッセージ取得関数を持っていたら呼ぶ
			static void runHandleMessage(const ComponentBasePtr& self, MessageTypeCarrier type, const MessageAttachment& attachment);

			// 親要素が変わった時関数を持っていたら呼ぶ
			static void runAfterChangeParent(const ComponentBasePtr& self, const GameObjectPtr& beforParent);

			// 衝突開始関数を持っていたら呼ぶ
			static void runOnCollisionEnter	(const ComponentBasePtr& self, const GameObjectPtr& other);

			// 衝突中関数を持っていたら呼ぶ
			static void runOnCollisionStay	(const ComponentBasePtr& self, const GameObjectPtr& other);

			// 衝突終了関数を持っていたら呼ぶ
			static void runOnCollisionExit	(const ComponentBasePtr& self, const GameObjectPtr& other);

			static VTable m_vtable;
		};

	private:

		VTable*				m_vtablePtr;
		ComponentBasePtr	m_selfPtr;
	};
//┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//┃ここから下は関数の実装
//┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

	template<class ComponentType>
	inline ComponentGameObjectFuncRunner::ComponentGameObjectFuncRunner(const std::weak_ptr<ComponentType>& componentPtr)
		: m_vtablePtr(&VTableInitializer<ComponentType>::m_vtable)
		, m_selfPtr(componentPtr)
	{
	}

	template<class ComponentType>
	typename ComponentGameObjectFuncRunner::VTable ComponentGameObjectFuncRunner::VTableInitializer<ComponentType>::m_vtable =
	{
		&ComponentGameObjectFuncRunner::VTableInitializer<ComponentType>::runHandleMessage,
		&ComponentGameObjectFuncRunner::VTableInitializer<ComponentType>::runAfterChangeParent,
		&ComponentGameObjectFuncRunner::VTableInitializer<ComponentType>::runOnCollisionEnter,
		&ComponentGameObjectFuncRunner::VTableInitializer<ComponentType>::runOnCollisionStay,
		&ComponentGameObjectFuncRunner::VTableInitializer<ComponentType>::runOnCollisionExit,
	};

	// メッセージ取得関数を持っていたら呼ぶ
	template<class ComponentType>
	inline void ComponentGameObjectFuncRunner::VTableInitializer<ComponentType>::runHandleMessage(const ComponentBasePtr& self, MessageTypeCarrier type, const MessageAttachment& attachment)
	{
		handleMessage_runner<void, MessageTypeCarrier, const MessageAttachment&>::checkAndRun(self.castPtr<ComponentType>(), type, attachment);
	}

	// 親要素が変わった時関数を持っていたら呼ぶ
	template<class ComponentType>
	inline void ComponentGameObjectFuncRunner::VTableInitializer<ComponentType>::runAfterChangeParent(const ComponentBasePtr& self, const GameObjectPtr& beforParent)
	{
		afterChangeParent_runner<void, const GameObjectPtr&>::checkAndRun(self.castPtr<ComponentType>(), beforParent);
	}

	// 衝突開始関数を持っていたら呼ぶ
	template<class ComponentType>
	inline void ComponentGameObjectFuncRunner::VTableInitializer<ComponentType>::runOnCollisionEnter(const ComponentBasePtr& self, const GameObjectPtr& other)
	{
		onCollisionEnter_runner<void, const GameObjectPtr&>::checkAndRun(self.castPtr<ComponentType>(), other);
	}

	// 衝突中関数を持っていたら呼ぶ
	template<class ComponentType>
	inline void ComponentGameObjectFuncRunner::VTableInitializer<ComponentType>::runOnCollisionStay(const ComponentBasePtr& self, const GameObjectPtr& other)
	{
		onCollisionStay_runner<void, const GameObjectPtr&>::checkAndRun(self.castPtr<ComponentType>(), other);
	}

	// 衝突終了関数を持っていたら呼ぶ
	template<class ComponentType>
	inline void ComponentGameObjectFuncRunner::VTableInitializer<ComponentType>::runOnCollisionExit(const ComponentBasePtr& self, const GameObjectPtr& other)
	{
		onCollisionExit_runner<void, const GameObjectPtr&>::checkAndRun(self.castPtr<ComponentType>(), other);
	}
}
#endif // !COMPONENT_GAME_OBJECT_FUNC_RUNNER_H_