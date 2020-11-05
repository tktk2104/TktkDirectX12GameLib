#ifndef POST_EFFECT_MATERIAL_DRAW_FUNC_ARGS_H_
#define POST_EFFECT_MATERIAL_DRAW_FUNC_ARGS_H_

namespace tktk
{
	// ポストエフェクトを描画する時に必要な引数
	struct PostEffectMaterialDrawFuncArgs
	{
		// 使用するビューポートハンドル
		size_t		viewportHandle;

		// 使用するシザー矩形ハンドル
		size_t		scissorRectHandle;

		// 使用するレンダーターゲット用ディスクリプタヒープハンドル
		size_t		rtvDescriptorHeapHandle;
	};
}
#endif // !POST_EFFECT_MATERIAL_DRAW_FUNC_ARGS_H_
