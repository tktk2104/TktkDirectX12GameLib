#ifndef BILLBOARD_MATERIAL_MANAGER_INIT_PARAM_H_
#define BILLBOARD_MATERIAL_MANAGER_INIT_PARAM_H_

/* class member */
#include <TktkContainer/ResourceContainer/ResourceContainerInitParam.h>
#include <TktkDX12Wrapper/Resource/GraphicsPipeLine/PipeLineState/PipeLineStateInitParam.h>

namespace tktk
{
	struct BillboardMaterialManagerInitParam
	{
		ShaderFilePaths								shaderFilePaths;
		tktkContainer::ResourceContainerInitParam	containerParam;
	};
}
#endif // !BILLBOARD_MATERIAL_MANAGER_INIT_PARAM_H_