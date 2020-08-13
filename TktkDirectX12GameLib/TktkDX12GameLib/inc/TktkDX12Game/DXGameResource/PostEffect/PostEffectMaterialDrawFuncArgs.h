#ifndef POST_EFFECT_MATERIAL_DRAW_FUNC_ARGS_H_
#define POST_EFFECT_MATERIAL_DRAW_FUNC_ARGS_H_

namespace tktk
{
	// ポストエフェクトを描画する時に必要な引数
	struct PostEffectMaterialDrawFuncArgs
	{
		// 使用するビューポートID
		unsigned int		viewportId;

		// 使用するシザー矩形ID
		unsigned int		scissorRectId;

		// 使用するレンダーターゲット用ディスクリプタヒープID
		unsigned int		rtvDescriptorHeapId;
	};
}
#endif // !POST_EFFECT_MATERIAL_DRAW_FUNC_ARGS_H_
