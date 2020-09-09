#ifndef SYSTEM_INDEX_BUFFER_TYPE_H_
#define SYSTEM_INDEX_BUFFER_TYPE_H_

namespace tktk
{
	// システムで使用しているインデックスバッファの種類
	enum class SystemIndexBufferType
	{
		Sprite = 0U,
		Sphere,
		Box,
	};
}
#endif // !SYSTEM_INDEX_BUFFER_TYPE_H_