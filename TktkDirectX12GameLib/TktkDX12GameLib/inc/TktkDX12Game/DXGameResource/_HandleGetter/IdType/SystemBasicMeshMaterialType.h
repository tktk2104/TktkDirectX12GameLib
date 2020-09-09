#ifndef SYSTEM_BASIC_MESH_MATERIAL_TYPE_H_
#define SYSTEM_BASIC_MESH_MATERIAL_TYPE_H_

namespace tktk
{
	// システムで使用している通常のメッシュマテリアルの種類
	enum class SystemBasicMeshMaterialType
	{
		Sphere = 0U,
		Box,
		SphereWireFrame,
		BoxWireFrame
	};
}
#endif // !SYSTEM_BASIC_MESH_MATERIAL_TYPE_H_