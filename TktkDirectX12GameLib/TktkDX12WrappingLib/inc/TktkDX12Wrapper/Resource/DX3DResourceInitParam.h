#ifndef DX_3D_RESOURCE_INIT_PARAM_H_
#define DX_3D_RESOURCE_INIT_PARAM_H_

#include "DescriptorHeap/DescriptorHeapInitParam.h"
#include "Buffer/BufferResourceInitParam.h"

namespace tktk
{
	struct DX3DResourceInitParam
	{
		unsigned int viewPortNum;
		unsigned int scissorRectNum;
		unsigned int pipeLineStateNum;
		unsigned int rootSignatureNum;
		DescriptorHeapInitParam descriptorHeapInitParam;
		BufferResourceInitParam bufferResourceInitParam;
	};
}
#endif // !DX_3D_RESOURCE_INIT_PARAM_H_