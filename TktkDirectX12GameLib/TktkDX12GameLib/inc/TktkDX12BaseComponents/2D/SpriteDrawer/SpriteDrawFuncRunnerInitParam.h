#ifndef SPRITE_DRAW_FUNC_RUNNER_INIT_PARAM_H_
#define SPRITE_DRAW_FUNC_RUNNER_INIT_PARAM_H_

namespace tktk
{
	struct SpriteDrawFuncRunnerInitParam
	{
	public:

		static SpriteDrawFuncRunnerInitParam& create();

	public:

		// 描画優先度を設定する
		SpriteDrawFuncRunnerInitParam& drawPriority(float value);

		// 使用するレンダーターゲットのディスクリプタヒープハンドルを設定する
		// ※初期パラメータはポストエフェクト適応対象
		SpriteDrawFuncRunnerInitParam& useRtvDescriptorHeapHandle(size_t value);

	private:

		static SpriteDrawFuncRunnerInitParam m_self;

	public:

		float	m_drawPriority				{ 0.0f };
		size_t	m_rtvDescriptorHeapHandle	{ 0U };
	};
}
#endif // !SPRITE_DRAW_FUNC_RUNNER_INIT_PARAM_H_