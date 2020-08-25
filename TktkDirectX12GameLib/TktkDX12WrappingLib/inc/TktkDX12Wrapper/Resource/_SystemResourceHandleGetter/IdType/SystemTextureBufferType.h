#ifndef SYSTEM_TEXTURE_BUFFER_TYPE_H_
#define SYSTEM_TEXTURE_BUFFER_TYPE_H_

namespace tktk
{
	// システムで使用しているテクスチャバッファの数
	constexpr unsigned int SystemTextureBufferNum = 1U;

	// システムで使用しているテクスチャバッファの種類
	enum class SystemTextureBufferType
	{
		White = 0U
	};
}
#endif // !SYSTEM_TEXTURE_BUFFER_TYPE_H_