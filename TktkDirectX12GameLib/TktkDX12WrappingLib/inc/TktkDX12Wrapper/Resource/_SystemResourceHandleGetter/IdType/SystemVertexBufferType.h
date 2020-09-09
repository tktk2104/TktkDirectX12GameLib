#ifndef SYSTEM_VERTEX_BUFFER_TYPE_H_
#define SYSTEM_VERTEX_BUFFER_TYPE_H_

namespace tktk
{
	// システムで使用している頂点バッファの種類
	enum class SystemVertexBufferType
	{
		Sprite = 0U,
		Sphere,
		Box,
	};
}
#endif // !SYSTEM_VERTEX_BUFFER_TYPE_H_