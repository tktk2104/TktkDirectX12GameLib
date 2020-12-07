#ifndef MESH_PMX_LOADER_H_
#define MESH_PMX_LOADER_H_

#include "Structs/MeshLoadPmxArgs.h"
#include "Structs/MeshLoadPmxReturnValue.h"

namespace tktk
{
	struct MeshDrawFuncRunnerInitParam;

	// pmx�t�@�C����ǂݍ���Ŋe��Q�[���̃��\�[�X�N���X�����N���X
	class MeshPmxLoader
	{
	public:

		// pmx�t�@�C����ǂݍ���Ŋe��Q�[���̃��\�[�X�N���X�����
		static MeshLoadPmxReturnValue loadPmx(const MeshLoadPmxArgs& args, const MeshDrawFuncRunnerInitParam& funcRunnerInitParam);
	};
}
#endif // !BASIC_MESH_PMX_LOADER_H_