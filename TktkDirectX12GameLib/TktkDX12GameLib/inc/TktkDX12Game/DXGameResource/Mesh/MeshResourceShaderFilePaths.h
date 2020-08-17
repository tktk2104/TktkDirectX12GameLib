#ifndef MESH_RESOURCE_SHADER_FILE_PATHS_H_
#define MESH_RESOURCE_SHADER_FILE_PATHS_H_

#include <string>
#include <TktkDX12Wrapper/Resource/GraphicsPipeLine/PipeLineState/PipeLineStateInitParam.h>

namespace tktk
{
	struct MeshResourceShaderFilePaths
	{
		ShaderFilePaths basicShaderFilePaths;
		std::string		monoColorShaderPsFilePath;
		std::string		writeShadowMapVsFilePath;
	};
}
#endif // !MESH_RESOURCE_SHADER_FILE_PATHS_H_