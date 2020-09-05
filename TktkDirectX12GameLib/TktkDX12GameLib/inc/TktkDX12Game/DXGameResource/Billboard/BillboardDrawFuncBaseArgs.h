#ifndef BILLBOARD_DRAW_FUNC_BASE_ARGS_H_
#define BILLBOARD_DRAW_FUNC_BASE_ARGS_H_

namespace tktk
{
	struct BillboardDrawFuncBaseArgs
	{
		// 使用するビューポートのハンドル
		unsigned int			viewportHandle;

		// 使用するシザー矩形のハンドル
		unsigned int			scissorRectHandle;

		// 使用するレンダーターゲット用のディスクリプタヒープハンドル
		unsigned int			rtvDescriptorHeapHandle;

		// 使用する深度ステンシル用のディスクリプタヒープハンドル
		unsigned int			dsvDescriptorHeapHandle;
	};
}
#endif // !BILLBOARD_DRAW_FUNC_BASE_ARGS_H_