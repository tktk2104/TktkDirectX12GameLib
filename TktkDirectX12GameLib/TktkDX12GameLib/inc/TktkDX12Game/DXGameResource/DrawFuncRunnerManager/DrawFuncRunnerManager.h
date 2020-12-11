#ifndef DRAW_FUNC_RUNNER_MANAGER_H_
#define DRAW_FUNC_RUNNER_MANAGER_H_

/* std::unique_ptr */
#include <memory>

namespace tktk
{
	/* class member */
	class PostEffectDrawFuncRunnerManager;
	//class BillboardDrawFuncRunnerManager;
	//class MeshDrawFuncRunnerManager;

	/* funcUseType */
	struct DrawFuncRunnerManagerInitParam;
	struct PostEffectDrawFuncRunnerInitParam;

	// 描画関数実行コンポーネントを管理するクラス
	class DrawFuncRunnerManager
	{
	public:

		explicit DrawFuncRunnerManager(const DrawFuncRunnerManagerInitParam& initParam);
		~DrawFuncRunnerManager();

	public: /* ポストエフェクトの描画関数を呼ぶコンポーネントの処理 */

		// 初期から存在するポストエフェクトの描画関数を作る
		void createSystemPostEffectDrawFuncRunner();

		// 新たなポストエフェクトの描画関数を呼ぶコンポーネントを作り、そのハンドルを返す
		size_t createPostEffectDrawFuncRunner(size_t postEffectMaterialHandle, const PostEffectDrawFuncRunnerInitParam& initParam);

		// 指定したポストエフェクトを実行開始する（他のポストエフェクトは停止する）
		void startPostEffect(size_t handle);

		// 全てのポストエフェクトを停止する
		void stopPostEffect();

	private:

		std::unique_ptr<PostEffectDrawFuncRunnerManager>	m_postEffectDrawFuncRunnerManager;
		//std::unique_ptr<BillboardDrawFuncRunnerManager>		m_billboardDrawFuncRunnerManager;
		//std::unique_ptr<MeshDrawFuncRunnerManager>			m_meshDrawFuncRunnerManager;
	};
}
#endif // !DRAW_FUNC_RUNNER_MANAGER_H_