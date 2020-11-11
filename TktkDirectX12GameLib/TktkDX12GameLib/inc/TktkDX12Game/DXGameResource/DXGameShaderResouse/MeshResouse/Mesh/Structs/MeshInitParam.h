#ifndef MESH_INIT_PARAM_H_
#define MESH_INIT_PARAM_H_

/* class member */
#include <vector>
#include "MeshPrimitiveTopology.h"

namespace tktk
{
	struct Subset;

	// ���b�V�������Ƃ��ɕK�v�ȏ��
	struct MeshInitParam
	{
		// �g�����_�o�b�t�@�̃n���h��
		size_t useVertexBufferHandle;

		// �g���C���f�b�N�X�o�b�t�@�̃n���h��
		size_t useIndexBufferHandle;

		// ���b�V�������C���f�b�N�X�̑���
		size_t indexNum;

		// ���b�V���̃|���S���̒��_���̖@��
		MeshPrimitiveTopology primitiveTopology;

		// �T�u�Z�b�g�i�g�p����}�e���A�����j
		std::vector<Subset> materialSlots;
	};
}
#endif // !MESH_INIT_PARAM_H_