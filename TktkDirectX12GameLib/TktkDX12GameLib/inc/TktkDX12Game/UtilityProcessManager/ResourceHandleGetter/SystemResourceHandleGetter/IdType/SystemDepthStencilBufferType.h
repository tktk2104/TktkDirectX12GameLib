#ifndef SYSTEM_DEPTH_STENCIL_BUFFER_TYPE_H_
#define SYSTEM_DEPTH_STENCIL_BUFFER_TYPE_H_

namespace tktk
{
	// システムで使用している深度ステンシルバッファの種類
	enum class SystemDsBufferType
	{
		Basic,
		ShadowMap
	};
}
#endif // !SYSTEM_DEPTH_STENCIL_BUFFER_TYPE_H_