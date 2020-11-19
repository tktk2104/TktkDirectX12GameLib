#ifndef DRAW_MESH_SHADER_FILE_PATHS_H_
#define DRAW_MESH_SHADER_FILE_PATHS_H_

#include <string>

namespace tktk
{
	struct DrawMeshShaderFilePaths
	{
		std::string simpleMeshVS;
		std::string skinningMeshVS;
		std::string basicMeshPS;

		std::string monoColorSimpleMeshVS;
		std::string monoColorSkinningMeshVS;
		std::string monoColorMeshPS;

		std::string simpleMeshShadowMapVs;
		std::string skinningMeshShadowMapVs;
	};
}
#endif // !DRAW_MESH_SHADER_FILE_PATHS_H_