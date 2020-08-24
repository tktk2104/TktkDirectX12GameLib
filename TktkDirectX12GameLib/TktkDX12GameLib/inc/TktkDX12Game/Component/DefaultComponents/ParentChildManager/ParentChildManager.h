#ifndef PARENT_CHILD_MANAGER_H_
#define PARENT_CHILD_MANAGER_H_

#include "../../ComponentBase.h"
#include "../../../GameObject/GameObjectPtr.h"
#include "ChildList.h"

namespace tktk
{
	// 親子関係を管理するコンポーネント
	// ※GameObjectを作ると勝手にAddComponentされる
	class ParentChildManager
		: public ComponentBase
	{
	public:

		ParentChildManager() = default;

	public:

		// 子要素のリストを更新する
		void updateContainer();

	public:

		// 全ての子供の全てのコンポーネントの親要素が変わった時関数を呼ぶ
		void runAfterChangeParentAll(const GameObjectPtr& beforParent);

		// 全ての子要素を削除する
		void removeChild(const GameObjectPtr& child);

		// 全ての子要素を殺す
		void destroyChildren();

		// 親要素を取得する
		const GameObjectPtr& getParent() const;

		// 親要素を設定する
		void setParent(const GameObjectPtr& parent);

		// 子要素のリストを取得する
		const std::forward_list<GameObjectPtr>& getChildren() const;

		// 自身の子要素から引数のタグを持ったゲームオブジェクトを取得する
		// ※複数該当オブジェクトがあった場合、最初に見つけた１つを取得する
		GameObjectPtr findGameObjectWithTag(int tag) const;

		// 自身の子要素から引数のタグを持ったゲームオブジェクトを全て取得する
		std::forward_list<GameObjectPtr> findGameObjectsWithTag(int tag) const;

		// 子要素を追加する
		void addChild(const GameObjectPtr& child);

		// 全ての子要素にメッセージを送信する
		void sendMessage(unsigned int messageId, const MessageAttachment& value);

	public:

		GameObjectPtr m_parent;

		ChildList m_childList;
	};
}
#endif // !PARENT_CHILD_MANAGER_H_