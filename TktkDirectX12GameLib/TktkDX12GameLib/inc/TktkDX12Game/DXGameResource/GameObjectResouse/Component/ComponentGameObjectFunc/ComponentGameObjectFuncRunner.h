#ifndef COMPONENT_GAME_OBJECT_FUNC_RUNNER_H_
#define COMPONENT_GAME_OBJECT_FUNC_RUNNER_H_

/* class member */
#include "../ComponentBasePtr.h"
#include "../../../../EventMessage/MessageTypeCarrier.h"

namespace tktk
{
	struct ComponentGameObjectFuncVTable;
	class GameObjectPtr;
	class MessageAttachment;

	// ゲームオブジェクトが使用するコンポーネントの関数を実行するクラス
	class ComponentGameObjectFuncRunner
	{
	public:

		ComponentGameObjectFuncRunner(const ComponentBasePtr& componentPtr, ComponentGameObjectFuncVTable* vtablePtr);

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

		ComponentGameObjectFuncVTable*	m_vtablePtr;
		ComponentBasePtr				m_selfPtr;
	};
}
#endif // !COMPONENT_GAME_OBJECT_FUNC_RUNNER_H_