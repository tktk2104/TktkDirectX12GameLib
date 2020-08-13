#ifndef DX_3D_RESOURCE_INIT_PARAM_H_
#define DX_3D_RESOURCE_INIT_PARAM_H_

#include "DescriptorHeap/DescriptorHeapInitParam.h"
#include "Buffer/BufferResourceNum.h"

namespace tktk
{
	struct DX3DResourceInitParam
	{
		unsigned int viewPortNum;
		unsigned int scissorRectNum;
		unsigned int pipeLineStateNum;
		unsigned int rootSignatureNum;
		DescriptorHeapInitParam descriptorHeapInitParam;
		BufferResourceNum bufferResourceInitParam;
	};
}
#endif // !DX_3D_RESOURCE_INIT_PARAM_H_