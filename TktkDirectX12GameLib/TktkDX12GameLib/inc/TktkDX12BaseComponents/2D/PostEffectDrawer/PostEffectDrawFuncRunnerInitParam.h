#ifndef POST_EFFECT_DRAW_FUNC_RUNNER_INIT_PARAM_H_
#define POST_EFFECT_DRAW_FUNC_RUNNER_INIT_PARAM_H_

namespace tktk
{
	struct PostEffectDrawFuncRunnerInitParam
	{
		// 描画優先度
		float	drawPriority				{ 10000.0f };

		// 描画先のレンダーターゲットのディスクリプタヒープハンドル
		size_t	rtvDescriptorHeapHandle		{ 0U };
	};
}
#endif // !POST_EFFECT_DRAW_FUNC_RUNNER_INIT_PARAM_H_