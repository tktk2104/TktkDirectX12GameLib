#ifndef MESH_PMX_LOADER_H_
#define MESH_PMX_LOADER_H_

#include "MeshLoadPmxArgs.h"
#include "MeshLoadPmxReturnValue.h"

namespace tktk
{
	// pmx�t�@�C����ǂݍ���Ŋe��Q�[���̃��\�[�X�N���X�����N���X
	class MeshPmxLoader
	{
	public:

		// pmx�t�@�C����ǂݍ���Ŋe��Q�[���̃��\�[�X�N���X�����
		static MeshLoadPmxReturnValue loadPmx(const MeshLoadPmxArgs& args);
	};
}
#endif // !BASIC_MESH_PMX_LOADER_H_