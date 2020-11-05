#ifndef COPY_BUFFER_INIT_PARAM_H_
#define COPY_BUFFER_INIT_PARAM_H_

#include "../BufferType.h"

namespace tktk
{
	struct UploadBufferInitParam
	{
	public:

		template <class CopyBufferType>
		static UploadBufferInitParam create(BufferType targetBufferType, size_t targetBufferHandle, const CopyBufferType& bufferData)
		{
			return UploadBufferInitParam(targetBufferType, targetBufferHandle, sizeof(CopyBufferType), &bufferData);
		}

	public:

		UploadBufferInitParam(BufferType targetBufferType, size_t targetBufferHandle, size_t bufferWidth, const void* dataTopPos)
			: targetBufferType(targetBufferType)
			, targetBufferHandle(targetBufferHandle)
			, bufferWidth(bufferWidth)
			, dataTopPos(dataTopPos) {}

	public:

		// アップロード対象のバッファーの種類
		BufferType		targetBufferType;

		// アップロード対象のバッファーのハンドル
		size_t			targetBufferHandle;

		// バッファーの大きさ
		size_t			bufferWidth;

		// バッファーの先頭ポインタ
		const void*		dataTopPos;
	};
}
#endif // !COPY_BUFFER_INIT_PARAM_H_