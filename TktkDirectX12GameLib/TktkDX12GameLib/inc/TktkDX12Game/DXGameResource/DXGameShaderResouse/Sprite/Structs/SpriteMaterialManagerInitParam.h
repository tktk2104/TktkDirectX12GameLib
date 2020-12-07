#ifndef SPRITE_MATERIAL_MANAGER_INIT_PARAM_H_
#define SPRITE_MATERIAL_MANAGER_INIT_PARAM_H_

/* class member */
#include <TktkContainer/ResourceContainer/ResourceContainerInitParam.h>
#include <TktkDX12Wrapper/Resource/GraphicsPipeLine/PipeLineState/PipeLineStateInitParam.h>

namespace tktk
{
	struct SpriteMaterialManagerInitParam
	{
		ShaderFilePaths								shaderFilePaths;
		tktkContainer::ResourceContainerInitParam	containerParam;
	};
}
#endif // !SPRITE_MATERIAL_MANAGER_INIT_PARAM_H_