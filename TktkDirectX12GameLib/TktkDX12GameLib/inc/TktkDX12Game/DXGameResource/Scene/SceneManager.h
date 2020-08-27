#ifndef SCENE_MANAGER_H_
#define SCENE_MANAGER_H_

#include <TktkContainer/ResourceContainer/ResourceContainer.h>
#include "SceneInstanceCarrier.h"

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
		unsigned int create(const std::shared_ptr<SceneBase>& scenePtr, SceneVTable* vtablePtr);

		// シーンを有効にする
		void enable(unsigned int handle);

		// シーンを無効にする
		void disable(unsigned int handle);

		// シーンの更新処理
		void update();

	private:

		tktkContainer::ResourceContainer<SceneInstanceCarrier> m_sceneArray;
	};
}
#endif // !SCENE_MANAGER_H_