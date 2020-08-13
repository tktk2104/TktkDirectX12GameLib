#ifndef DX_GAME_DRAW_FUNC_ARGS_H_
#define DX_GAME_DRAW_FUNC_ARGS_H_

namespace tktk
{
	struct DXGameDrawFuncArgs
	{
		unsigned int viewportId;
		unsigned int scissorRectId;

		unsigned int rtvDescriptorHeapId;
	};
}
#endif // !DX_GAME_DRAW_FUNC_ARGS_H_