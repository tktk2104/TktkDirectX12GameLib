#ifndef POST_EFFECT_MATERIAL_DRAW_FUNC_ARGS_H_
#define POST_EFFECT_MATERIAL_DRAW_FUNC_ARGS_H_

namespace tktk
{
	// ポストエフェクトを描画する時に必要な引数
	struct PostEffectMaterialDrawFuncArgs
	{
		// 使用するビューポートハンドル
		unsigned int		viewportHandle;

		// 使用するシザー矩形ハンドル
		unsigned int		scissorRectHandle;

		// 使用するレンダーターゲット用ディスクリプタヒープハンドル
		unsigned int		rtvDescriptorHeapHandle;
	};
}
#endif // !POST_EFFECT_MATERIAL_DRAW_FUNC_ARGS_H_
