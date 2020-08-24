#ifndef SCENE_MANAGER_H_
#define SCENE_MANAGER_H_

#include <TktkContainer/HeapArray/HeapArray.h>
#include "SceneInstanceCarrier.h"

namespace tktk
{
	// シーン管理クラス
	class SceneManager
	{
	public:

		SceneManager(unsigned int sceneNum);
		~SceneManager() = default;

	public:

		// シーンを作成して追加する
		void create(unsigned int id, const std::shared_ptr<SceneBase>& scenePtr, SceneVTable* vtablePtr);

		// シーンを有効にする
		void enable(unsigned int id);

		// シーンを無効にする
		void disable(unsigned int id);

		// シーンの更新処理
		void update();

	private:

		tktkContainer::HeapArray<SceneInstanceCarrier> m_sceneArray;
	};
}
#endif // !SCENE_MANAGER_H_