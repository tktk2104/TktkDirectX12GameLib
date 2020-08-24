#ifndef DX_GAME_RESOURCE_NUM_H_
#define DX_GAME_RESOURCE_NUM_H_

#include "Mesh/MeshResourceNum.h"

namespace tktk
{
	// �Q�[���Ŏg�p����\�ʓI�ȃ��\�[�X�̐�
	struct DXGameResourceNum
	{
		// �V�[����
		unsigned int sceneNum				{};

		// �T�E���h��
		unsigned int soundNum				{};

		// �X�v���C�g�}�e���A����
		unsigned int spriteMaterialNum		{};

		// ���C���QD�}�e���A����
		unsigned int line2DMaterialNum		{};

		// ���b�V���֘A���\�[�X��
		MeshResourceNum meshResourceNum		{};

		// �|�X�g�G�t�F�N�g�}�e���A����
		unsigned int postEffectMaterialNum	{};

		// �J������
		unsigned int cameraNum				{};

		// ���C�g��
		unsigned int lightNum				{};
	};
}
#endif // !DX_GAME_RESOURCE_NUM_H_