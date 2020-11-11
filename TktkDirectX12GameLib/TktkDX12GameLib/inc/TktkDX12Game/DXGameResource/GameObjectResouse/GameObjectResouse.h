#ifndef GAME_OBJECT_RESOUSE_H_
#define GAME_OBJECT_RESOUSE_H_

/* std::unique_ptr */
#include <memory>

/* std::type_index */
#include <typeindex>

/* std::forward_list */
#include <forward_list>

/* funcUseType */
#include "GameObject/GameObjectPtr.h"
#include "GameObject/GameObjectTagCarrier.h"
#include "../../EventMessage/MessageTypeCarrier.h"
#include "Component/ComponentCollisionFunc/CollisionGroupTypeCarrier.h"
#include "Component/ComponentBasePtr.h"

namespace tktk
{
	class GameObjectManager;
	class ComponentManager;
	class MessageAttachment;
	struct ComponentListVTable;
	struct ComponentVTableBundle;
	class ComponentBase;

	// ゲームオブジェクトに関係するリソースを管理するクラス
	class GameObjectResouse
	{
	public:

		GameObjectResouse();
		~GameObjectResouse();

	public:

		// 前フレームに追加されたコンポーネントをメインリストに追加する
		void movePreFrameAddedNode();

		// 更新処理
		void update();

		// 死んだインスタンスを削除する
		void removeDeadInstance();

		// 描画処理
		void draw();

	public: /* ゲームオブジェクト関係の処理 */

		// 全てのGameObjectにメッセージを送信する
		void runHandleMessageAll(MessageTypeCarrier type, const MessageAttachment& attachment);

		// ゲームオブジェクトを作成し、そのポインタを返す
		GameObjectPtr createGameObject();

		// 引数のタグを持ったゲームオブジェクトを取得する
		// ※複数該当オブジェクトがあった場合、最初に見つけた１つを取得する
		GameObjectPtr findGameObjectWithTag(GameObjectTagCarrier tag) const;

		// 引数のタグを持ったゲームオブジェクトを全て取得する
		std::forward_list<GameObjectPtr> findGameObjectsWithTag(GameObjectTagCarrier tag) const;

		// 引数のタグを持ったゲームオブジェクトを全て削除する
		void destroyGameObjectsWithTag(GameObjectTagCarrier tag);

	public: /* コンポーネント関係の処理 */

		// コンポーネントの型ごとの更新優先度を設定する
		// ※デフォルト（0.0f）で値が小さい程、早く実行される
		void addRunFuncPriority(std::type_index type, float priority);

		// 衝突判定の組み合わせを追加する
		void addCollisionGroup(CollisionGroupTypeCarrier firstGroup, CollisionGroupTypeCarrier secondGroup);

		// 引数のコンポーネントを追加する
		ComponentBasePtr addComponent(std::type_index type, ComponentVTableBundle* vtablePtrBundle, ComponentListVTable* listVtablePtr, const GameObjectPtr& user, const std::shared_ptr<ComponentBase>& componentPtr);

	private:

		std::unique_ptr<GameObjectManager>	m_gameObjectManager;
		std::unique_ptr<ComponentManager>	m_componentManager;
	};
}
#endif // !GAME_OBJECT_RESOUSE_H_