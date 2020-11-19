#ifndef COPY_BUFFER_INIT_PARAM_H_
#define COPY_BUFFER_INIT_PARAM_H_

#include <vector>
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

		template <class CopyBufferType>
		static UploadBufferInitParam create(BufferType targetBufferType, size_t targetBufferHandle, const std::vector<CopyBufferType>& bufferData)
		{
			return UploadBufferInitParam(targetBufferType, targetBufferHandle, sizeof(CopyBufferType) * bufferData.size(), bufferData.data());
		}

	public:

		UploadBufferInitParam(BufferType targetBufferType, size_t targetBufferHandle, size_t bufferWidth, const void* dataTopPos)
			: targetBufferType(targetBufferType)
			, targetBufferHandle(targetBufferHandle)
			, bufferWidth((bufferWidth + 0xff) & ~0xff)
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