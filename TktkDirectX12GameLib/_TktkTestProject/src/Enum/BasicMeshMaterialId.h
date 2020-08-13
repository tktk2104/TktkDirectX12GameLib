#ifndef BASIC_MESH_MATERIAL_ID_H_
#define BASIC_MESH_MATERIAL_ID_H_

#include "ToIntFunc.h"

enum class BasicMeshMaterialId
{
	MikuMatStart		= 0U,
	MikuMatEnd			= MikuMatStart			+ 17U,
	ElementSphereStart,
	ElementSphereEnd	= ElementSphereStart	+ 7U,

	Count
};

constexpr unsigned int BasicMeshMaterialNum = static_cast<unsigned int>(BasicMeshMaterialId::Count);

#endif // !BASIC_MESH_MATERIAL_ID_H_
