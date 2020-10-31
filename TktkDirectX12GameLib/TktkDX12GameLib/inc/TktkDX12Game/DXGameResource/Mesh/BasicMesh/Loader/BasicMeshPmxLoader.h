#ifndef BASIC_MESH_PMX_LOADER_H_
#define BASIC_MESH_PMX_LOADER_H_

#include "BasicMeshLoadPmxArgs.h"
#include "BasicMeshLoadPmxReturnValue.h"

namespace tktk
{
	// pmx�t�@�C����ǂݍ���Ŋe��Q�[���̃��\�[�X�N���X�����N���X
	class BasicMeshPmxLoader
	{
	public:

		// pmx�t�@�C����ǂݍ���Ŋe��Q�[���̃��\�[�X�N���X�����
		static BasicMeshLoadPmxReturnValue loadPmx(const BasicMeshLoadPmxArgs& args);
	};
}
#endif // !BASIC_MESH_PMX_LOADER_H_