#ifndef GAME_OBJECT_MANAGER_H_
#define GAME_OBJECT_MANAGER_H_

#include <memory>
#include <forward_list>
#include "GameObjectPtr.h"
#include "GameObjectTagCarrier.h"
#include "../EventMessage/MessageTypeCarrier.h"
#include "../EventMessage/MessageAttachment.h"


namespace tktk
{
	class GameObject;

	// ゲームオブジェクト管理クラス
	class GameObjectManager
	{
	public:

		GameObjectManager() = default;

	public:

		void update();

		// 前フレームに追加されたゲームオブジェクトをメインリストに追加する
		void movePreFrameAddedNode();

		// 死んだゲームオブジェクトを削除する
		void removeDeadObject();

	public:

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

	private:

		std::forward_list<std::shared_ptr<GameObject>> m_gameObjectList;
		std::forward_list<std::shared_ptr<GameObject>> m_newGameObjectList;
	};
}
#endif // !GAME_OBJECT_MANAGER_H_