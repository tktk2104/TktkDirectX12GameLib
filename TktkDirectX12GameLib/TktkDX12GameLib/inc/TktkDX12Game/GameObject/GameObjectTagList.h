#ifndef GAME_OBJECT_TAG_LIST_H_
#define GAME_OBJECT_TAG_LIST_H_

#include <unordered_set>

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
		void addTag(int tag);

		// 引数のタグを削除する
		void removeTag(int tag);

		// 引数のタグを所持しているかを判定する
		bool contain(int tag) const;

	private:

		std::unordered_set<unsigned int> m_tagList;
	};
}
#endif // !GAME_OBJECT_TAG_LIST_H_