#ifndef MESH_MATERIAL_INIT_PARAM_H_
#define MESH_MATERIAL_INIT_PARAM_H_

/* class member */
#include <TktkMath/Structs/Color.h>

namespace tktk
{
	// ���b�V���̃}�e���A�������Ƃ��K�v�ȏ��
	struct MeshMaterialInitParam
	{
		// �g���p�C�v���C���X�e�[�g�̃n���h��
		size_t								usePipeLineStateHandle;

		// �g���f�B�X�N���v�^�q�[�v�̃n���h��
		size_t								useDescriptorHeapHandle;

		// �}�e���A���̊���
		tktkMath::Color						materialAmbient		{ 0.25f, 1.0f };

		// �}�e���A���̊g�U���ˌ�
		tktkMath::Color						materialDiffuse		{ 0.25f, 1.0f };

		// �}�e���A���̋��ʔ��ˌ�
		tktkMath::Color						materialSpecular	{ 0.25f, 1.0f };

		// �}�e���A���̎��Ȕ���
		tktkMath::Color						materialEmissive	{ 0.25f, 1.0f };

		// �}�e���A���̋P�x
		float								materialShiniess	{ 1.0f };
	};
}
#endif // !MESH_MATERIAL_INIT_PARAM_H_