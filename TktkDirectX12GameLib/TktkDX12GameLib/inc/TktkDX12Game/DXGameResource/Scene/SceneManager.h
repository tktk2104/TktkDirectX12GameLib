#ifndef SCENE_MANAGER_H_
#define SCENE_MANAGER_H_

#include <TktkContainer/ResourceContainer/ResourceContainer.h>
#include "SceneInstanceCarrier.h"
#include "SceneDataInitParam.h"
#include "../../GameObject/GameObjectTagCarrier.h"

namespace tktk
{
	// シーン管理クラス
	class SceneManager
	{
	public:

		explicit SceneManager(const tktkContainer::ResourceContainerInitParam& initParam);
		~SceneManager() = default;

	public:

		// シーンを作り、そのリソースのハンドルを返す
		size_t create(const SceneDataInitParam& initParam);

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