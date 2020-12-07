#ifndef BILLBOARD_MATERIAL_INSTANCE_VERT_DATA_H_
#define BILLBOARD_MATERIAL_INSTANCE_VERT_DATA_H_

/* class member */
#include <TktkMath/Structs/Color.h>
#include <TktkMath/Structs/Vector2.h>
#include <TktkMath/Structs/Vector3.h>

namespace tktk
{
	struct BillboardMaterialInstanceVertData
	{
		// �r���r�[�h�̍��W
		tktkMath::Vector3	billboardPosition	{ tktkMath::Vector3_v::zero };

		// �r���{�[�h�̉�]�p�x
		float				billboardAngle		{ 0.0f };

		// �r���{�[�h�̃X�P�[��
		tktkMath::Vector2	billboardScale		{ tktkMath::Vector2_v::one };

		// �e�N�X�`��UV�̃I�t�Z�b�g�l
		tktkMath::Vector2	textureUvOffset		{ tktkMath::Vector2_v::zero };

		// �e�N�X�`��UV�ɏ�Z����l
		tktkMath::Vector2	textureUvMulRate	{ tktkMath::Vector2_v::zero };

		// �e�N�X�`���̃T�C�Y�i�s�N�Z���j
		tktkMath::Vector2	textureSize			{ tktkMath::Vector2_v::one };

		// �X�v���C�g�̒��S�_�i�����j
		tktkMath::Vector2	textureCenterRate	{ tktkMath::Vector2_v::zero };

		// �p�f�B���O
		float				pad[2]{  };

		// �u�����h���[�g
		tktkMath::Color		blendRate			{ tktkMath::Color_v::white };
	};
}
#endif // !BILLBOARD_MATERIAL_INSTANCE_VERT_DATA_H_