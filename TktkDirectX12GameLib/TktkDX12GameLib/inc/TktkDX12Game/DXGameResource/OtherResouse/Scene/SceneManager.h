#ifndef SCENE_MANAGER_H_
#define SCENE_MANAGER_H_

/* tktkContainer::ResourceContainer */
#include <TktkContainer/ResourceContainer/ResourceContainer.h>

/* funcUseType */
#include "../../GameObjectResouse/GameObject/GameObjectTagCarrier.h"

namespace tktk
{
	class SceneInstanceCarrier;
	struct SceneInitParam;

	// シーン管理クラス
	class SceneManager
	{
	public:

		explicit SceneManager(const tktkContainer::ResourceContainerInitParam& initParam);
		~SceneManager();

	public:

		// シーンを作り、そのリソースのハンドルを返す
		size_t create(const SceneInitParam& initParam);

		// シーンの終了時に削除するゲームオブジェクトタグを設定する
		void setSceneEndDestroyGameObjectTag(size_t handle, GameObjectTagCarrier tag);

		// シーンを有効にする
		void enable(size_t handle);

		// シーンを無効にする
		void disable(size_t handle);

		// シーンの更新処理
		void update();

	private:

		tktkContainer::ResourceContainer<SceneInstanceCarrier> m_sceneArray;
	};
}
#endif // !SCENE_MANAGER_H_