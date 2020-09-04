#ifndef SPRITE_CONSTANT_BUFFER_DATA_H_
#define SPRITE_CONSTANT_BUFFER_DATA_H_

#include <TktkMath/Structs/Color.h>
#include <TktkMath/Structs/Vector2.h>

namespace tktk
{
	// �X�v���C�g�`��Ɏg�p����萔�o�b�t�@���
	struct SpriteMaterialCbufferData
	{
		// �u�����h���[�g
		tktkMath::Color		blendRate			{ 1.0f, 1.0f, 1.0f, 1.0f };

		// �X�N���[���T�C�Y
		tktkMath::Vector2	screenSize			{ 640.0f, 480.0f };

		// �p�f�B���O
		float				pad[2]{};
	};
}
#endif // !SPRITE_CONSTANT_BUFFER_DATA_H_