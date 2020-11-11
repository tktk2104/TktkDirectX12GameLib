#ifndef LINE_2D_MATERIAL_MANAGER_INIT_PARAM_H_
#define LINE_2D_MATERIAL_MANAGER_INIT_PARAM_H_

/* class member */
#include <TktkContainer/ResourceContainer/ResourceContainerInitParam.h>
#include <TktkDX12Wrapper/Resource/GraphicsPipeLine/PipeLineState/PipeLineStateInitParam.h>

namespace tktk
{
	struct Line2DMaterialManagerInitParam
	{
		ShaderFilePaths								shaderFilePaths;
		tktkContainer::ResourceContainerInitParam	containerParam;
	};
}
#endif // !LINE_2D_MATERIAL_MANAGER_INIT_PARAM_H_