#ifndef MESH_MATERIAL_MANAGER_INIT_PARAM_H_
#define MESH_MATERIAL_MANAGER_INIT_PARAM_H_

/* class member */
#include <TktkContainer/ResourceContainer/ResourceContainerInitParam.h>
#include <TktkDX12Wrapper/Resource/GraphicsPipeLine/PipeLineState/PipeLineStateInitParam.h>

namespace tktk
{
	struct MeshMaterialManagerInitParam
	{
		ShaderFilePaths								basicShaderFilePaths;
		std::string									monoColorShaderPsFilePath;
		tktkContainer::ResourceContainerInitParam	containerParam;
	};
}
#endif // !MESH_MATERIAL_MANAGER_INIT_PARAM_H_
