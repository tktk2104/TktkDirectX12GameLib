#ifndef MESH_PMD_LOADER_H_
#define MESH_PMD_LOADER_H_

#include "Structs/MeshLoadPmdArgs.h"
#include "Structs/MeshLoadPmdReturnValue.h"

namespace tktk
{
	struct MeshDrawFuncRunnerInitParam;

	// pmd�t�@�C����ǂݍ���Ŋe��Q�[���̃��\�[�X�N���X�����N���X
	class MeshPmdLoader
	{
	public:

		// pmd�t�@�C����ǂݍ���Ŋe��Q�[���̃��\�[�X�N���X�����
		static MeshLoadPmdReturnValue loadPmd(const MeshLoadPmdArgs& args, const MeshDrawFuncRunnerInitParam& funcRunnerInitParam);
	};
}
#endif // !MESH_PMD_LOADER_H_