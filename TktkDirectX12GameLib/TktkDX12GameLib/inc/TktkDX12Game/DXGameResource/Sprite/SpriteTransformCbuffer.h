#ifndef SPRITE_TRANSFORM_CBUFFER_H_
#define SPRITE_TRANSFORM_CBUFFER_H_

namespace tktk
{
	// �X�v���C�g�̍��W�ϊ��̒萔�o�b�t�@�̏��
	struct SpriteTransformCbuffer
	{
		// ���[���h�s��ihsls�̎d�l��Afloat4x3�j
		float				worldMatrix[12]{};
	};
}
#endif // !SPRITE_TRANSFORM_CBUFFER_H_