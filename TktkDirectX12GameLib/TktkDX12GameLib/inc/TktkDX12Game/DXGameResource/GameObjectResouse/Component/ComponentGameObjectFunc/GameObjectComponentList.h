#ifndef GAME_OBJECT_COMPONENT_LIST_H_
#define GAME_OBJECT_COMPONENT_LIST_H_

/* std::type_index */
#include <typeindex>

/* std::forward_list */
#include <forward_list>

/* class member */
#include "../ComponentBasePtr.h"
#include "../../../../EventMessage/MessageTypeCarrier.h"

namespace tktk
{
	class ComponentGameObjectFuncRunner;
	struct ComponentGameObjectFuncVTable;
	class MessageAttachment;
	class GameObjectPtr;

	// ゲームオブジェクトが持っているコンポーネントのリスト
	class GameObjectComponentList
	{
	public:

		GameObjectComponentList();
		~GameObjectComponentList();

	public:

		// 新たなコンポーネントを追加する
		void add(const ComponentBasePtr& componentPtr, ComponentGameObjectFuncVTable* vtablePtr);

		// 引数の型のコンポーネントを取得する
		// ※取得できなかったらnullptrを返す
		// ※複数該当するコンポーネントがあったら最初に見つけた１つを返す
		ComponentBasePtr find(std::type_index type) const;

		// 引数の型のコンポーネントを全て取得する
		std::forward_list<ComponentBasePtr> findAll(std::type_index type) const;

		// 全てのメッセージ取得関数を呼ぶ
		void runHandleMessageAll(MessageTypeCarrier type, const MessageAttachment& attachment) const;

		// 全ての「子供の全てのコンポーネントの親要素が変わった時関数」を呼ぶ
		void runAfterChangeParentAll(const GameObjectPtr& beforParent) const;

		// 全てのコンポーネントの衝突開始関数を呼ぶ
		void runOnCollisionEnterAll(const GameObjectPtr& other);

		// 全てのコンポーネントの衝突中関数を呼ぶ
		void runOnCollisionStayAll(const GameObjectPtr& other);

		// 全てのコンポーネントの衝突終了関数を呼ぶ
		void runOnCollisionExitAll(const GameObjectPtr& other);

		// 現在のフレームで衝突処理を行ったオブジェクトリストをクリアする
		void clearHitObjectList();

		// 全てのコンポーネントを殺す
		void destroyAll() const;

		// 前フレームに追加されたコンポーネントをメインリストに追加する
		void movePreFrameAddedNode();

		// 死亡フラグが立っているコンポーネントを削除する
		void removeDeadComponent();

	private:

		std::forward_list<GameObjectPtr> m_curFrameHitObjectList;
		std::forward_list<ComponentGameObjectFuncRunner> m_componentList;
		std::forward_list<ComponentGameObjectFuncRunner> m_nextFrameAddNodeList;
	};
}
#endif // !GAME_OBJECT_COMPONENT_LIST_H_
