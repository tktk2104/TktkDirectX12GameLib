#ifndef GAME_OBJECT_MANAGER_H_
#define GAME_OBJECT_MANAGER_H_

#include <memory>
#include <forward_list>
#include "GameObjectPtr.h"
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

		// 死んだゲームオブジェクトを削除する
		void removeDeadObject();

	public:

		// 全てのGameObjectにメッセージを送信する
		void runHandleMessageAll(unsigned int messageId, const MessageAttachment& value);

		// ゲームオブジェクトを作成し、そのポインタを返す
		GameObjectPtr createGameObject();

		// 引数のタグを持ったゲームオブジェクトを取得する
		// ※複数該当オブジェクトがあった場合、最初に見つけた１つを取得する
		GameObjectPtr findGameObjectWithTag(int tag) const;

		// 引数のタグを持ったゲームオブジェクトを全て取得する
		std::forward_list<GameObjectPtr> findGameObjectsWithTag(int tag) const;

	private:

		std::forward_list<std::shared_ptr<GameObject>> m_gameObjectList;
	};
}
#endif // !GAME_OBJECT_MANAGER_H_