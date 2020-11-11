#ifndef MESH_PMD_LOADER_H_
#define MESH_PMD_LOADER_H_

#include "MeshLoadPmdArgs.h"
#include "MeshLoadPmdReturnValue.h"

namespace tktk
{
	// pmd�t�@�C����ǂݍ���Ŋe��Q�[���̃��\�[�X�N���X�����N���X
	class MeshPmdLoader
	{
	public:

		// pmd�t�@�C����ǂݍ���Ŋe��Q�[���̃��\�[�X�N���X�����
		static MeshLoadPmdReturnValue loadPmd(const MeshLoadPmdArgs& args);
	};
}
#endif // !MESH_PMD_LOADER_H_
