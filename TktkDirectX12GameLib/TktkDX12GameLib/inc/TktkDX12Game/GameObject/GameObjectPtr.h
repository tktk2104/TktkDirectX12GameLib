#ifndef GAME_OBJECT_PTR_H_
#define GAME_OBJECT_PTR_H_

#include <memory>

namespace tktk
{
	// 前方宣言
	class GameObject;

	// ゲームオブジェクトを扱うためのポインタ
	class GameObjectPtr
	{
	public:

		// nullptrとして作成する
		GameObjectPtr() = default;

		// 引数のweakポインタを持つ形で作成する
		explicit GameObjectPtr(const std::weak_ptr<GameObject>& weakPtr);

	public:

		// 自身のポインタが指しているゲームオブジェクトが死んでいるか判定する
		bool expired() const;

		// 引数のポインタと同一なゲームオブジェクトかを判定する
		bool isSame(const GameObjectPtr& other) const;

		// ポインタにアクセスする
		std::shared_ptr<GameObject> operator ->() const;

	private:

		std::weak_ptr<GameObject> m_gameObjectPtr;
	};
}
#endif // !GAME_OBJECT_PTR_H_