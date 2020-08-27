#ifndef BASIC_MESH_MATERIAL_ID_H_
#define BASIC_MESH_MATERIAL_ID_H_

#include "ToIntFunc.h"

enum class BasicMeshMaterialId
{
	Count
};

constexpr unsigned int BasicMeshMaterialNum = static_cast<unsigned int>(BasicMeshMaterialId::Count);

#endif // !BASIC_MESH_MATERIAL_ID_H_
