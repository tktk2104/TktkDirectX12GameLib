#ifndef SPRITE_MATERIAL_INSTANCE_DATA_H_
#define SPRITE_MATERIAL_INSTANCE_DATA_H_

/* class member */
#include <TktkMath/Structs/Color.h>
#include <TktkMath/Structs/Vector2.h>
//#include <TktkMath/Structs/Matrix3.h>

namespace tktk
{
	struct SpriteMaterialInstanceData
	{
		// ���[���h�s��ihsls�̎d�l��Afloat4x3�j
		float				worldMatrix[12]		{};

		// �e�N�X�`��UV�̃I�t�Z�b�g�l
		tktkMath::Vector2	textureUvOffset		{ tktkMath::Vector2_v::zero };

		// �e�N�X�`��UV�ɏ�Z����l
		tktkMath::Vector2	textureUvMulRate	{ tktkMath::Vector2_v::zero };

		// �e�N�X�`���̃T�C�Y�i�s�N�Z���j
		tktkMath::Vector2	textureSize			{ tktkMath::Vector2_v::one };

		// �X�v���C�g�̒��S�_�i�����j
		tktkMath::Vector2	textureCenterRate	{ tktkMath::Vector2_v::zero };

		// �u�����h���[�g
		tktkMath::Color		blendRate			{ tktkMath::Color_v::white };
	};
}
#endif // !SPRITE_MATERIAL_INSTANCE_DATA_H_