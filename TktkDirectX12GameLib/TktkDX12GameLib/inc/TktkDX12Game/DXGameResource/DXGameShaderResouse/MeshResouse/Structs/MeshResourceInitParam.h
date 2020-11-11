#ifndef MESH_RESOURCE_INIT_PARAM_H_
#define MESH_RESOURCE_INIT_PARAM_H_

#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/MeshResouse/Mesh/Structs/MeshManagerInitParam.h"
#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/MeshResouse/MeshMaterial/Structs/MeshMaterialManagerInitParam.h"

namespace tktk
{
	struct MeshResourceInitParam
	{
		MeshManagerInitParam						meshMgrParam;
		MeshMaterialManagerInitParam				meshMatMgrParam;
		tktkContainer::ResourceContainerInitParam	skeletonMgrParam;
		tktkContainer::ResourceContainerInitParam	motionMgrParam;
	};
}
#endif // !MESH_RESOURCE_INIT_PARAM_H_