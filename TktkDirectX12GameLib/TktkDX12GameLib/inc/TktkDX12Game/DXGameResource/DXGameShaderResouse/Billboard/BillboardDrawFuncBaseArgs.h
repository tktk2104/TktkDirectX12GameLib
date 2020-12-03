#ifndef BILLBOARD_DRAW_FUNC_BASE_ARGS_H_
#define BILLBOARD_DRAW_FUNC_BASE_ARGS_H_

namespace tktk
{
	// ビルボードの描画に必要な変数
	struct BillboardDrawFuncBaseArgs
	{
		// 使用するビューポートのハンドル
		size_t	viewportHandle;

		// 使用するシザー矩形のハンドル
		size_t	scissorRectHandle;

		// 使用するレンダーターゲット用のディスクリプタヒープハンドル
		size_t	rtvDescriptorHeapHandle;

		// 使用する深度ステンシル用のディスクリプタヒープハンドル
		size_t	dsvDescriptorHeapHandle;
	};
}
#endif // !BILLBOARD_DRAW_FUNC_BASE_ARGS_H_