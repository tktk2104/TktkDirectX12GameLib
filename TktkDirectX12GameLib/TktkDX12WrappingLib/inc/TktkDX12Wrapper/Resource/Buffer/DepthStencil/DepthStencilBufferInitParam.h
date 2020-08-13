#ifndef DEPTH_STENCIL_BUFFER_INIT_PARAM_H_
#define DEPTH_STENCIL_BUFFER_INIT_PARAM_H_

#include <TktkMath/Structs/Vector2.h>

namespace tktk
{
	struct DepthStencilBufferInitParam
	{
		tktkMath::Vector2	depthStencilSize;
		bool				useAsShaderResource;
	};
}
#endif // !DEPTH_STENCIL_BUFFER_INIT_PARAM_H_