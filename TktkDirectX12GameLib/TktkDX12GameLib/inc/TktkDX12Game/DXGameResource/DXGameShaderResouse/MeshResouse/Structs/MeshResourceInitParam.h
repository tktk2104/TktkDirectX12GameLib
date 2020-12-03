#ifndef MESH_RESOURCE_INIT_PARAM_H_
#define MESH_RESOURCE_INIT_PARAM_H_

#include <TktkContainer/ResourceContainer/ResourceContainerInitParam.h>
#include "DrawMeshShaderFilePaths.h"

namespace tktk
{
	struct MeshResourceInitParam
	{
		DrawMeshShaderFilePaths						shaderFilePaths;
		tktkContainer::ResourceContainerInitParam	meshMgrParam;
		tktkContainer::ResourceContainerInitParam	meshMatMgrParam;
		tktkContainer::ResourceContainerInitParam	skeletonMgrParam;
		tktkContainer::ResourceContainerInitParam	motionMgrParam;
	};
}
#endif // !MESH_RESOURCE_INIT_PARAM_H_