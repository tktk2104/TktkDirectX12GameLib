#ifndef DRAW_GAME_AREA_SIZE_CBUFFER_DATA_H_
#define DRAW_GAME_AREA_SIZE_CBUFFER_DATA_H_

/* class member */
#include <TktkMath/Structs/Vector2.h>

namespace tktk
{
	// �X�N���[���T�C�Y�̒萔�o�b�t�@�̏��
	struct DrawGameAreaSizeCBufferData
	{
		// �Q�[���`��G���A�T�C�Y
		tktkMath::Vector2	drawGameAreaSize	{ 640.0f, 480.0f };

		// �p�f�B���O
		float				pad[2]				{  };
	};
}
#endif // !DRAW_GAME_AREA_SIZE_CBUFFER_DATA_H_