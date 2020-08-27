#ifndef BASIC_MESH_LOAD_PMD_ARGS_H_
#define BASIC_MESH_LOAD_PMD_ARGS_H_

#include <string>

namespace tktk
{
	// pmd�t�@�C����ǂݍ��ނƂ��ɕK�v�ȏ��
	struct BasicMeshLoadPmdArgs
	{
		// �쐬����ʏ탁�b�V������ID
		unsigned int createBasicMeshId;

		// �쐬����X�P���g������ID
		unsigned int createSkeletonId;

		// �ǂݍ��ރt�@�C���p�X
		std::string filePath;
	};
}
#endif // !BASIC_MESH_LOAD_PMD_ARGS_H_
