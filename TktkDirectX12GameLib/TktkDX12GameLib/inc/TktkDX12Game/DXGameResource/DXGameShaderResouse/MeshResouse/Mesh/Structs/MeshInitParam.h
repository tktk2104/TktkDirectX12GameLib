#ifndef MESH_INIT_PARAM_H_
#define MESH_INIT_PARAM_H_

/* class member */
#include <vector>
#include <TktkDX12Wrapper/_BaseObjects/PrimitiveTopology.h>
#include <TktkDX12Wrapper/Resource/Buffer/Vertex/VertexDataCarrier.h>

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
		PrimitiveTopology primitiveTopology;

		// �T�u�Z�b�g�i�g�p����}�e���A�����j
		std::vector<Subset> materialSlots;

		// �C���X�^���X�`�掞�A�C���X�^���X���̒��_�o�b�t�@���
		VertexDataCarrier instanceVertParam { 0U, 0U, nullptr };
	};
}
#endif // !MESH_INIT_PARAM_H_