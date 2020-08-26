#ifndef POST_EFFECT_MATERIAL_INIT_PARAM_H_
#define POST_EFFECT_MATERIAL_INIT_PARAM_H_

#include <vector>

namespace tktk
{
	// ポストエフェクトのマテリアルを作る時に必要な情報
	struct PostEffectMaterialInitParam
	{
		// 使用するパイプラインステートハンドル
		unsigned int usePipeLineStateHandle;

		// 使用するディスクリプタヒープハンドル
		unsigned int useDescriptorHeapHandle;

		// 描画後自動でクリアするレンダーターゲットビュー用のディスクリプタヒープハンドルの配列
		std::vector<unsigned int> autoClearRtvDescriptorHeapHandleArray;
	};
}
#endif // !POST_EFFECT_MATERIAL_INIT_PARAM_H_