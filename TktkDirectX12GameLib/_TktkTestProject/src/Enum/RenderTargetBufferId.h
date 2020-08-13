#ifndef RENDER_TARGET_BUFFER_ID_H_
#define RENDER_TARGET_BUFFER_ID_H_

#include "ToIntFunc.h"

enum class RenderTargetBufferId
{
	PostEffectTest = 0U,

	Count
};

constexpr unsigned int RenderTargetBufferNum = static_cast<unsigned int>(RenderTargetBufferId::Count);

#endif // !RENDER_TARGET_BUFFER_ID_H_
