#ifndef BUFFER_RESOURCE_INIT_PARAM_H_
#define BUFFER_RESOURCE_INIT_PARAM_H_

namespace tktk
{
	struct BufferResourceInitParam
	{
		unsigned int vertexBufferNum;
		unsigned int indexBufferNum;
		unsigned int constantBufferNum;
		unsigned int textureBufferNum;
		unsigned int depthStencilBufferNum;
		unsigned int renderTargetBufferNum;
	};
}
#endif // !BUFFER_RESOURCE_INIT_PARAM_H_