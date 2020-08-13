#ifndef RTV_DESCRIPTOR_HEAP_ID_H_
#define RTV_DESCRIPTOR_HEAP_ID_H_

#include "ToIntFunc.h"

enum class RtvDescriptorHeapId
{
	PostEffectTest = 0U,

	Count
};

constexpr unsigned int RtvDescriptorHeapNum = static_cast<unsigned int>(RtvDescriptorHeapId::Count);

#endif // !RTV_DESCRIPTOR_HEAP_ID_H_