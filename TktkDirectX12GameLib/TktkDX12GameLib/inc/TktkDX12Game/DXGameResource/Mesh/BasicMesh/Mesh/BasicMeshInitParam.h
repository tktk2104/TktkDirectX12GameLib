#ifndef BASIC_MESH_INIT_PARAM_H_
#define BASIC_MESH_INIT_PARAM_H_

#include <vector>
#include "../Structs/Subset.h"
#include "../../Structs/MeshPrimitiveTopology.h"

namespace tktk
{
	// �ʏ탁�b�V�������Ƃ��ɕK�v�ȏ��
	struct BasicMeshInitParam
	{
		// �g�����_�o�b�t�@�̃n���h��
		size_t useVertexBufferHandle;

		// �g���C���f�b�N�X�o�b�t�@�̃n���h��
		size_t useIndexBufferHandle;

		// ���b�V�������C���f�b�N�X�̑���
		size_t indexNum;

		MeshPrimitiveTopology primitiveTopology;

		// �T�u�Z�b�g�i�g�p����}�e���A�����j
		std::vector<Subset> materialSlots;
	};
}
#endif // !BASIC_MESH_INIT_PARAM_H_