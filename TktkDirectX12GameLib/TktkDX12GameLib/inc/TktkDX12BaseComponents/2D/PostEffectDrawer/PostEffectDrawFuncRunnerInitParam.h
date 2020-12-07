#ifndef POST_EFFECT_DRAW_FUNC_RUNNER_INIT_PARAM_H_
#define POST_EFFECT_DRAW_FUNC_RUNNER_INIT_PARAM_H_

namespace tktk
{
	struct PostEffectDrawFuncRunnerInitParam
	{
	public:

		static PostEffectDrawFuncRunnerInitParam& create();

	public:

		static PostEffectDrawFuncRunnerInitParam m_self;

	private:

		PostEffectDrawFuncRunnerInitParam() = default;

	public:

		// 描画優先度
		float	drawPriority				{ 1000.0f };

		// 使用するレンダーターゲットのディスクリプタヒープハンドル
		// ※初期パラメータはゲーム描画エリア
		size_t	rtvDescriptorHeapHandle		{ 0U };
	};
}
#endif // !POST_EFFECT_DRAW_FUNC_RUNNER_INIT_PARAM_H_