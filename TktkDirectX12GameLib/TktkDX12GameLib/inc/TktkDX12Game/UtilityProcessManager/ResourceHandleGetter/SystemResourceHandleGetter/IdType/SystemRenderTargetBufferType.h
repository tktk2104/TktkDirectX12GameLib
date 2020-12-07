#ifndef SYSTEM_RENDER_TARGET_BUFFER_TYPE_H_
#define SYSTEM_RENDER_TARGET_BUFFER_TYPE_H_

namespace tktk
{
	// システムで使用しているレンダーターゲットの種類
	enum class SystemRtBufferType
	{
		BackBuffer_1,
		BackBuffer_2,
		DrawGameArea,
		PostEffectTarget,
	};
}
#endif // !SYSTEM_RENDER_TARGET_BUFFER_TYPE_H_