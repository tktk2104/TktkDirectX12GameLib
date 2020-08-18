#ifndef CHILD_LIST_H_
#define CHILD_LIST_H_

#include <forward_list>
#include "../../../GameObject/GameObjectPtr.h"
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
		// ※複数該当オブジェクトがあった場合、最初に見つけた１つを取得する
		GameObjectPtr findGameObjectWithTag(int tag) const;

		// 自身の子要素から引数のタグを持ったゲームオブジェクトを全て取得する
		std::forward_list<GameObjectPtr> findGameObjectsWithTag(int tag) const;

		// リストを更新する
		void updateContainer();

		// 指定の子要素をリストから削除する
		void remove(const GameObjectPtr& gameObject);

		// 全ての子要素を殺す
		void destroyAll();

		// 全ての子要素にメッセージを送信する
		void sendMessage(unsigned int messageId, const MessageAttachment& value);

	private:

		std::forward_list<GameObjectPtr> m_childList;
		std::forward_list<GameObjectPtr> m_newComponentList;
	};
}
#endif // !CHILD_LIST_H_