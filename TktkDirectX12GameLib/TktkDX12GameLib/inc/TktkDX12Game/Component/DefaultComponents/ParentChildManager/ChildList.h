#ifndef CHILD_LIST_H_
#define CHILD_LIST_H_

#include <forward_list>
#include "../../../GameObject/GameObjectPtr.h"
#include "../../../GameObject/GameObjectTagCarrier.h"
#include "../../../EventMessage/MessageTypeCarrier.h"
#include "../../../EventMessage/MessageAttachment.h"

namespace tktk
{
	// 子要素のリスト
	class ChildList
	{
	public:

		ChildList() = default;
		~ChildList() {}

	public:

		// 新たな子要素を追加
		// ※追加した子要素は次のフレームでメインのリストに追加される
		void addChild(const GameObjectPtr& child);

		// 子要素のリストを取得
		const std::forward_list<GameObjectPtr>& getChildren() const;

		// 自身の子要素から引数のタグを持ったゲームオブジェクトを取得する
		// ※該当オブジェクトが無かった場合、空のGameObjectPtrを取得する
		// ※複数該当オブジェクトがあった場合、最初に見つけた１つを取得する
		GameObjectPtr findGameObjectWithTag(GameObjectTagCarrier tag) const;

		// 自身の子要素から引数のタグを持ったゲームオブジェクトを全て取得する
		std::forward_list<GameObjectPtr> findGameObjectsWithTag(GameObjectTagCarrier tag) const;

		// 前フレームに追加されたゲームオブジェクトをメインリストに追加する
		void movePreFrameAddedNode();

		// 死亡フラグが立っているゲームオブジェクトを削除する
		void removeDeadComponent();

		// 指定の子要素をリストから削除する
		void remove(const GameObjectPtr& gameObject);

		// 全ての子要素を殺す
		void destroyAll();

		// 全ての子要素にメッセージを送信する
		void sendMessage(MessageTypeCarrier type, const MessageAttachment& attachment);

	private:

		std::forward_list<GameObjectPtr> m_childList;
		std::forward_list<GameObjectPtr> m_newGameObjectList;
	};
}
#endif // !CHILD_LIST_H_