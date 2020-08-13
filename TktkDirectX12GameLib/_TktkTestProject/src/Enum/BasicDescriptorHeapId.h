#ifndef BASIC_DESCRIPTOR_HEAP_ID_H_
#define BASIC_DESCRIPTOR_HEAP_ID_H_

#include "ToIntFunc.h"

enum class BasicDescriptorHeapId
{
	PostEffectTest = 0U,
	TestTexture,
	MikuMatStart,
	MikuMatEnd = MikuMatStart + 17U,
	VertexColorPolygon,

	Count
};

constexpr unsigned int BasicDescriptorHeapNum = static_cast<unsigned int>(BasicDescriptorHeapId::Count);

#endif // !BASIC_DESCRIPTOR_HEAP_ID_H_