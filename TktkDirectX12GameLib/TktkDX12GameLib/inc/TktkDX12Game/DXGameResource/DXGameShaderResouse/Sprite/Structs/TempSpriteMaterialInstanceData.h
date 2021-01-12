#ifndef TEMP_SPRITE_MATERIAL_INSTANCE_DATA_H_
#define TEMP_SPRITE_MATERIAL_INSTANCE_DATA_H_

/* class member */
#include <TktkMath/Structs/Color.h>
#include <TktkMath/Structs/Vector2.h>
#include <TktkMath/Structs/Matrix3.h>

namespace tktk
{
	struct TempSpriteMaterialInstanceData
	{
		// ���[���h�s��
		tktkMath::Matrix3	worldMatrix			{ tktkMath::Matrix3_v::identity };

		// �g�p����e�N�X�`���s�N�Z����
		tktkMath::Vector2	texturePixelCount	{ tktkMath::Vector2_v::zero };

		// �e�N�X�`���s�N�Z���̃I�t�Z�b�g�l
		tktkMath::Vector2	texturePixelOffset	{ tktkMath::Vector2_v::zero };

		// �e�N�X�`��UV�ɏ�Z����l
		tktkMath::Vector2	textureUvMulRate	{ tktkMath::Vector2_v::one };

		// �X�v���C�g�̒��S�_�i�����j
		tktkMath::Vector2	textureCenterRate	{ tktkMath::Vector2_v::zero };

		// �u�����h���[�g
		tktkMath::Color		blendRate			{ tktkMath::Color_v::white };
	};
}
#endif // !TEMP_SPRITE_MATERIAL_INSTANCE_DATA_H_