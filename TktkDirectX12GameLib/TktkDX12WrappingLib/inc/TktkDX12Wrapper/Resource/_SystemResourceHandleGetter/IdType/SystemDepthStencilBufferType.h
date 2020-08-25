#ifndef SYSTEM_DEPTH_STENCIL_BUFFER_TYPE_H_
#define SYSTEM_DEPTH_STENCIL_BUFFER_TYPE_H_

namespace tktk
{
	// システムで使用している深度ステンシルバッファの数
	constexpr unsigned int SystemDsBufferNum = 2U;

	// システムで使用している深度ステンシルバッファの種類
	enum class SystemDsBufferType
	{
		Basic		= 0U,
		ShadowMap	= 1U
	};
}
#endif // !SYSTEM_DEPTH_STENCIL_BUFFER_TYPE_H_