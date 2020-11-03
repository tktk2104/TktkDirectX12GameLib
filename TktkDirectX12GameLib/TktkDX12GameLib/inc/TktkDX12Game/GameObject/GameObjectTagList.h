#ifndef GAME_OBJECT_TAG_LIST_H_
#define GAME_OBJECT_TAG_LIST_H_

#include <unordered_set>
#include "GameObjectTagCarrier.h"

namespace tktk
{
	// ゲームオブジェクトのタグを管理するコンテナ
	class GameObjectTagList
	{
	public:

		GameObjectTagList() = default;
		~GameObjectTagList() = default;

	public:

		// 引数のタグを追加する
		void addTag(GameObjectTagCarrier tag);

		// 引数のタグを削除する
		void removeTag(GameObjectTagCarrier tag);

		// 引数のタグを所持しているかを判定する
		bool contain(GameObjectTagCarrier tag) const;

	private:

		std::unordered_set<GameObjectTagCarrier> m_tags;
	};
}
#endif // !GAME_OBJECT_TAG_LIST_H_