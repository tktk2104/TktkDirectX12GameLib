#ifndef SPRITE_CBUFFER_DATA_H_
#define SPRITE_CBUFFER_DATA_H_

/* class member */
#include <TktkMath/Structs/Color.h>
#include <TktkMath/Structs/Vector2.h>

namespace tktk
{
	// �X�v���C�g�`��Ɏg�p����萔�o�b�t�@���
	struct SpriteMaterialCBufferData
	{
		// �u�����h���[�g
		tktkMath::Color		blendRate			{ tktkMath::Color_v::white };

		// �X�N���[���T�C�Y
		tktkMath::Vector2	screenSize			{ 640.0f, 480.0f };

		// �p�f�B���O
		float				pad[2]{};
	};
}
#endif // !SPRITE_CBUFFER_DATA_H_