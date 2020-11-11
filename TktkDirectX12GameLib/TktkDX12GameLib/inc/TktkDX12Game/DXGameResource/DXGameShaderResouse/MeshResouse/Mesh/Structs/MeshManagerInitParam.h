#ifndef MESH_MANAGER_INIT_PARAM_H_
#define MESH_MANAGER_INIT_PARAM_H_

/* class member */
#include <TktkContainer/ResourceContainer/ResourceContainerInitParam.h>
#include <TktkDX12Wrapper/Resource/GraphicsPipeLine/PipeLineState/PipeLineStateInitParam.h>

namespace tktk
{
	struct MeshManagerInitParam
	{
		std::string									writeShadowMapVsFilePath;
		tktkContainer::ResourceContainerInitParam	containerParam;
	};
}
#endif // !MESH_MANAGER_INIT_PARAM_H_