#ifndef SPRITE_CBUFFER_UPDATE_FUNC_ARGS_H_
#define SPRITE_CBUFFER_UPDATE_FUNC_ARGS_H_

/* class member */
#include <TktkMath/Structs/Vector2.h>
#include <TktkMath/Structs/Matrix3.h>

namespace tktk
{
	struct SpriteCBufferUpdateFuncArgs
	{
		// ���[���h�s��
		tktkMath::Matrix3	worldMatrix;

		// �X�v���C�g�̒��S�ʒu�i�����j
		tktkMath::Vector2	spriteCenterRate;
	};
}
#endif // !SPRITE_CBUFFER_UPDATE_FUNC_ARGS_H_