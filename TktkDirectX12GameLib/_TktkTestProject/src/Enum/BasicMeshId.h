#ifndef BASIC_MESH_ID_H_
#define BASIC_MESH_ID_H_

#include "ToIntFunc.h"

enum class BasicMeshId
{
	Miku = 0U,
	ElementSphereStart,
	ElementSphereEnd = ElementSphereStart + 7U,

	Count
};

constexpr unsigned int BasicMeshNum = static_cast<unsigned int>(BasicMeshId::Count);

#endif // !BASIC_MESH_ID_H_