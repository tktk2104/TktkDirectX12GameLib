#ifndef MESH_LOAD_PMX_ARGS_H_
#define MESH_LOAD_PMX_ARGS_H_

#include <string>

namespace tktk
{
	struct MeshLoadPmxArgs
	{
		// �쐬����ʏ탁�b�V������ID
		int createBasicMeshId;

		// �쐬����X�P���g������ID
		int createSkeletonId;

		// �ǂݍ��ރt�@�C���p�X
		std::string filePath;
	};
}
#endif // !MESH_LOAD_PMX_ARGS_H_