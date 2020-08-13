#ifndef SYSTEM_RENDER_TARGET_BUFFER_TYPE_H_
#define SYSTEM_RENDER_TARGET_BUFFER_TYPE_H_

namespace tktk
{
	// システムで使用しているレンダーターゲットの数
	constexpr unsigned int SystemRtBufferNum = 2U;

	// システムで使用しているレンダーターゲットの種類
	enum class SystemRtBufferType
	{
		BackBuffer_1	= 0U,
		BackBuffer_2	= 1U,
	};
}
#endif // !SYSTEM_RENDER_TARGET_BUFFER_TYPE_H_