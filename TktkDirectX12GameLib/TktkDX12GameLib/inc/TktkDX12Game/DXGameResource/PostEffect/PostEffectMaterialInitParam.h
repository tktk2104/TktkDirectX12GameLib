#ifndef POST_EFFECT_MATERIAL_INIT_PARAM_H_
#define POST_EFFECT_MATERIAL_INIT_PARAM_H_

namespace tktk
{
	// ポストエフェクトのマテリアルを作る時に必要な情報
	struct PostEffectMaterialInitParam
	{
		// 使用するパイプラインステートハンドル
		unsigned int usePipeLineStateHandle;

		// 使用するディスクリプタヒープハンドル
		unsigned int useDescriptorHeapHandle;
	};
}
#endif // !POST_EFFECT_MATERIAL_INIT_PARAM_H_