#ifndef DX_3D_RESOURCE_INIT_PARAM_H_
#define DX_3D_RESOURCE_INIT_PARAM_H_

#include <TktkContainer/ResourceContainer/ResourceContainerInitParam.h>
#include "GraphicsPipeLine/GraphicsPipeLineResourceNum.h"
#include "DescriptorHeap/DescriptorHeapNum.h"
#include "Buffer/BufferResourceNum.h"

namespace tktk
{
	struct DX3DResourceNum
	{
		tktkContainer::ResourceContainerInitParam	viewPortNum;
		tktkContainer::ResourceContainerInitParam	scissorRectNum;
		GraphicsPipeLineResourceNum					graphicsPipeLineResourceNum;
		DescriptorHeapNum							descriptorHeapNum;
		BufferResourceNum							bufferResourceNum;
	};
}
#endif // !DX_3D_RESOURCE_INIT_PARAM_H_