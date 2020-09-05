#ifndef SPRITE_TRANSFORM_CBUFFER_H_
#define SPRITE_TRANSFORM_CBUFFER_H_

#include <TktkMath/Structs/Vector2.h>

namespace tktk
{
	// �X�v���C�g�̍��W�ϊ��̒萔�o�b�t�@�̏��
	struct SpriteTransformCbuffer
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
		tktkMath::Vector2	spriteCenterRate	{ tktkMath::Vector2_v::zero };
	};
}
#endif // !SPRITE_TRANSFORM_CBUFFER_H_