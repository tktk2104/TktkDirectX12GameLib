#ifndef DX_GAME_DRAW_FUNC_ARGS_H_
#define DX_GAME_DRAW_FUNC_ARGS_H_

namespace tktk
{
	// DirectX12を使用した描画に共通して要求される変数
	struct DXGameDrawFuncArgs
	{
		// 使用するビューポートのID
		size_t viewportHandle;

		// 使用するシーザー矩形のID
		size_t scissorRectHandle;

		// 使用するレンダーターゲット用ディスクリプタヒープのID
		size_t rtvDescriptorHeapHandle;
	};
}
#endif // !DX_GAME_DRAW_FUNC_ARGS_H_