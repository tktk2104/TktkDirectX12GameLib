#ifndef COPY_BUFFER_INIT_PARAM_H_
#define COPY_BUFFER_INIT_PARAM_H_

#include "../BufferType.h"

namespace tktk
{
	struct CopyBufferInitParam
	{
		// コピー対象のバッファーの種類
		BufferType		targetBufferType;

		// コピー対象のバッファーのハンドル
		unsigned int	targetBufferHandle;

		// バッファーの大きさ
		unsigned int	bufferWidth;

		// バッファーの先頭ポインタ
		const void*		dataTopPos;
	};
}
#endif // !COPY_BUFFER_INIT_PARAM_H_