#ifndef POST_EFFECT_DRAW_FUNC_RUNNER_MANAGER_H_
#define POST_EFFECT_DRAW_FUNC_RUNNER_MANAGER_H_

/* tktkContainer::ResourceContainer */
#include <TktkContainer/ResourceContainer/ResourceContainer.h>

#include "../../GameObjectResouse/Component/ComponentPtr.h"

namespace tktk
{
	/* class member */
	class PostEffectDrawFuncRunner;

	/* funcUseType */
	struct PostEffectDrawFuncRunnerInitParam;

	// ポストエフェクトの描画関数を呼ぶコンポーネントの管理クラス
	class PostEffectDrawFuncRunnerManager
	{
	public:

		PostEffectDrawFuncRunnerManager(const tktkContainer::ResourceContainerInitParam& initParam);
		~PostEffectDrawFuncRunnerManager();

		PostEffectDrawFuncRunnerManager(const PostEffectDrawFuncRunnerManager& other) = delete;
		PostEffectDrawFuncRunnerManager& operator = (const PostEffectDrawFuncRunnerManager& other) = delete;

	public:

		// 初期から存在するポストエフェクトの描画関数を作る
		void createSystemResource();

		// 新たなポストエフェクトの描画関数を呼ぶコンポーネントを作り、そのハンドルを返す
		size_t create(size_t postEffectMaterialHandle, const PostEffectDrawFuncRunnerInitParam& initParam);

		// 指定したポストエフェクトを実行開始する（他のポストエフェクトは停止する）
		void startPostEffect(size_t handle);

		// 全てのポストエフェクトを停止する
		void stopPostEffect();

	private:

		void createDrawGameAreaDrawFuncRunner();

		void createNotPostEffectDrawFuncRunner();

		void createPostEffectMonochromeDrawFuncRunner();

		void createPostEffectNegativeDrawFuncRunner();

		void createPostEffectAveragingBlurDrawFuncRunner();

		void createPostEffectEmbossDrawFuncRunner();

		void createPostEffectSharpnessDrawFuncRunner();

	private:

		// 描画エリア描画用のポストエフェクト
		tktk::ComponentPtr<PostEffectDrawFuncRunner> m_drawGameAreaDrawFuncRunner;

		// 何も処理を行わないポストエフェクトの実行コンポーネント
		tktk::ComponentPtr<PostEffectDrawFuncRunner> m_notPostEffectDrawFuncRunner;

		tktkContainer::ResourceContainer<tktk::ComponentPtr<PostEffectDrawFuncRunner>> m_drawFuncRunnerList;
	};
}
#endif // !POST_EFFECT_DRAW_FUNC_RUNNER_MANAGER_H_